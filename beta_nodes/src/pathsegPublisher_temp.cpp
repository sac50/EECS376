// pathsegPublisher.cpp
// inputs: 	a file of waypoints to generate the initial path segments,
//			"cmd_corr" - corrective heading, map x-y
//			"replanning" - where new path suggestions are published
// outputs: 	"paths" - top of a list of path segments to traverse
//		"polySeg" - the current polyline segment, likely to only be handed to steering

//Publish paths from some source, maybe 

//TODO: add ability to push some new segment to the front of the queue
//want to convert waypoints to path segments first, publish,
//publish new path segments under some conditions 
//like when stopped in front of obstacles
#include<ros/ros.h>
#include<geometry_msgs/Twist.h> //data type for velocities
#include<beta_nodes/PathSegment.h>
#include<tf/transform_datatypes.h> //for tf::getYaw and create quaternion
#include <beta_nodes/steeringMsg.h>
#include <beta_nodes/orange.h>
#include "Path.h"
#include <vector>
#include <deque>

#define Hz 10
#define LINE 1
#define ARC 2
#define SPIN 3

using namespace std;

bool inAvoid=false;
bool needToReplan=false;

Vector position;
beta_nodes::PathSegment avoidancePatch;
beta_nodes::PathSegment polySeg;
vector<beta_nodes::PathSegment> pathQueue;
deque<Vector> polyLinePoints;

void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
}

void avoidanceCallback(const beta_nodes::PathSegment::ConstPtr& pth){
	//ROS_INFO("%d",pth->seg_type);
	avoidancePatch = *pth;
}

void orangeCallback(const beta_nodes::orange::ConstPtr& orange){
	//Callback from the orange detection thingy
	//Ideally will hand me a delightful array of points along the line, preferably atleast 10cm apart
	//Should try to not republish points over and over, but we can handle that if need be
	//A path will be published at large as having current position as start, the farthest out orange as end, and a heading
	// defined by the current mini segment, this should work I think
	//Please let the points be passed from farthest to closest, I plan on using a vector to store the points
	// and vectors have stack like properties I hope to exploit.
	//As noted we have a ~1m deadzone in front of the kinect where we have no data
	// This could be an issue so we need to keep that in mind when we hit debugging
	Vector potato;
	potato.x = orange->posX;
	potato.y = orange->posY;
	polyLinePoints.push_front(potato);
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"paths");//name of this node
	ros::NodeHandle n;
	ros::Publisher pubseg = n.advertise<beta_nodes::PathSegment>("paths",1);
	ros::Publisher pubPoly = n.advertise<beta_nodes::PathSegment>("polySeg",1);
	ros::Subscriber sub = n.subscribe("cmd_corr",1,steeringCallback);
	ros::Subscriber sub1 = n.subscribe("replanning",1,avoidanceCallback);

	ros::Duration elapsed_time; // define a variable to hold elapsed time
	ros::Rate naptime(Hz); //will perform sleeps to enforce loop rate of "10" Hz
	while (!ros::Time::isValid()) {} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid

	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	ROS_INFO("birthday started as %f", birthday.toSec());

	int segNum = 0; //The ass end of our current PathQueue vector
	beta_nodes::PathSegment curPathSeg; // create an instance of datatype PathSegment
	//dummy population of PathSegment fields
//	curPathSeg.curvature = 3.14;
//	curPathSeg.seg_length=0.0;
/*
	curPathSeg.ref_point.x=-3.52;
	curPathSeg.ref_point.y=20.77;
	curPathSeg.init_point.x=5.53;
	curPathSeg.init_point.y=11.92;
//	curPathSeg.seg_number=123;
	curPathSeg.seg_type=1;
	curPathSeg.seg_psi = atan2((curPathSeg.ref_point.y-curPathSeg.init_point.y),(curPathSeg.ref_point.x-curPathSeg.init_point.x));
	//ROS_INFO("Current Segment PSI: %f", curPathSeg.seg_psi);
//	curPathSeg.init_tan_angle=tf::createQuaternionMsgFromYaw(1.23);
//	curPathSeg.max_speeds.linear.x=3.45;
//	curPathSeg.max_speeds.angular.z=1.23;
//	curPathSeg.accel_limit=4.56;
//	curPathSeg.decel_limit=5.67;
	pathQueue.push_back(curPathSeg);
	Vector point;
	point.x = -3.52;
	point.y = 20.77;
	polyLinePoints.push_back(point);
	point.x = -1.54;
	point.y = 19.26;
	polyLinePoints.push_back(point);
	point.x = 0.46;
	point.y = 16.31;
	polyLinePoints.push_back(point);
	*/
	
	// SEE THE BLUE SHIT ABOVE
	// We ignore that now, but I hate deleting things so it stays for now please

	double DistToGo;

	while (ros::ok()) // do work here
	{
		ros::spinOnce();
		
		//avoidancePatch.init_point.x += position.x;
		//avoidancePatch.init_point.y += position.y;
		//avoidancePatch.ref_point.x = avoidancePatch.init_point.x + cos(curPathSeg.seg_psi);
		//avoidancePatch.ref_point.y = avoidancePatch.init_point.y + sin(curPathSeg.seg_psi);
		//avoidancePatch.seg_psi = curPathSeg.seg_psi;
		if(pathQueue.size()>0){
			//curPathSeg = pathQueue.back();  This is wrong
			if(polyLinePoints.size()>0){
				curPathSeg.ref_point.x = polyLinePoints[0].x;
				curPathSeg.ref_point.y = polyLinePoints[0].y;
				curPathSeg.init_point.x = position.x;
				curPathSeg.init_point.y = position.y;
				curPathSeg.seg_type = 1;
				curPathSeg.seg_psi = atan2((curPathSeg.ref_point.y-curPathSeg.init_point.y),(curPathSeg.ref_point.x-curPathSeg.init_point.x));
				polySeg.ref_point.x = polyLinePoints.back().x;
				polySeg.ref_point.y = polyLinePoints.back().y;
				polySeg.init_point.x = position.x;
				polySeg.init_point.y = position.y;
				polySeg.seg_type=1;
				polySeg.seg_psi = atan2((polySeg.ref_point.y-polySeg.init_point.y),(polySeg.ref_point.x-polySeg.init_point.x));
			}
			else{
				polySeg.seg_type=0;
				curPathSeg.seg_type=0;
			}
		}
		else{
			curPathSeg.seg_type = 0;
			polySeg.seg_type = 0;
		}
		DistToGo = sqrt(pow(polySeg.ref_point.x-position.x,2)+pow(polySeg.ref_point.y-position.y,2));
//		curPathSeg.seg_length= elapsed_time.toSec();
		//ROS_INFO("sqrt((%2.2f- %2.2f)^2 + (%2.2f- %2.2f)^2) = %f",curPathSeg.ref_point.x,position.x,curPathSeg.ref_point.y,position.y,DistToGo);
		if(DistToGo<0.1 && curPathSeg.seg_type!=0){
			ROS_INFO("Popped type: %d %d", curPathSeg.seg_type,segNum);
			if(polyLinePoints.size()>0){
				polyLinePoints.pop_back();
			}
			if(polyLinePoints.size()==0){
				pathQueue.pop_back();
				curPathSeg.seg_type=0;			
			}
				
		}
		//ROS_INFO("Current: %f %f",curPathSeg.ref_point.x,curPathSeg.ref_point.y);
		pubseg.publish(curPathSeg); // publish the path segment
		pubPoly.publish(polySeg);



		naptime.sleep(); // this will achieve the desired update rate (10Hz)
	}
	return 0; //only get here if node told to shut down ( ros::ok() is false )
}
