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
#include<geometry_msgs/PointStamped.h>
#include<beta_nodes/PathSegment.h>
#include<tf/transform_datatypes.h> //for tf::getYaw and create quaternion
#include <beta_nodes/steeringMsg.h>
#include <beta_nodes/freeSpace.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <math.h>
#include "Path.h"
#include <vector>
#include <deque>

#define Hz 50
#define LINE 1
#define ARC 2
#define SPIN 3

using namespace std;

bool inAvoid=false;
bool needToReplan=false;

Vector position;
Vector last_potato;
beta_nodes::PathSegment avoidancePatch;
beta_nodes::PathSegment polySeg;
vector<beta_nodes::PathSegment> pathQueue;
deque<Vector> polyLinePoints;
geometry_msgs::Point mp;	//markerpoint;

//Steering Callback
//Just gets robot position from steering node
void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
}

//Deprecated Callback for object avoidance
//Used to be used to notify this node that we are attempting a work around to avoid an object
//Avoidance paths had a type value of 4 to indicate what they were
void avoidanceCallback(const beta_nodes::PathSegment::ConstPtr& pth){
	//ROS_INFO("%d",pth->seg_type);
	avoidancePatch = *pth;
}

//Helper method, calculates linear distance between two points
double diff(Vector one, Vector two){
	return sqrt(pow(one.x-two.x,2)+pow(one.y-two.y,2));
}

// only for find orange
void orangeCallback1(const geometry_msgs::PointStamped::ConstPtr& orange) {
	Vector potato;
	potato.x = orange->point.x;
	potato.y = orange->point.y;
	if (polyLinePoints.size() == 0) {
		polyLinePoints.push_front(potato);
		ROS_INFO("Point Taken:  x: %f y: %f", potato.x, potato.y);
		last_potato = potato;
	}
	else if (diff(last_potato, potato)>0.1) {
		polyLinePoints.push_front(potato);
		ROS_INFO("Point Taken: x: %f y: %f", potato.x, potato.y);
		last_potato = potato;
	} 

}
void orangeCallback(const beta_nodes::freeSpace::ConstPtr& orange) {
	bool obstacleFound = orange->obstacleFound;
	geometry_msgs::PointStamped point = orange->point;

	Vector potato;

	ROS_INFO("ORANGE CALLBACK");
	ROS_INFO("OBSTACLE FOUND %d", obstacleFound);
	potato.x = point.point.x;
	potato.y = point.point.y;
	if (polyLinePoints.size() == 0) {
		polyLinePoints.push_front(potato);
		ROS_INFO("Point Taken:  x: %f y: %f", potato.x, potato.y);
		last_potato = potato;
	}
	else if (diff(last_potato, potato)>0.1) {
		polyLinePoints.push_front(potato);
		ROS_INFO("Point Taken: x: %f y: %f", potato.x, potato.y);
		last_potato = potato;
	}

	// If no obstacle found, clear the poly line vector list
	// This allows the way point to be the desired point to be steered to
//	if (!obstacleFound) {
	//	polyLinePoints.clear();
//	}
}
/*
void orangeCallback(const geometry_msgs::PointStamped::ConstPtr& orange){
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
	potato.x = orange->point.x;
	potato.y = orange->point.y;
	if(polyLinePoints.size()==0){
		polyLinePoints.push_front(potato);
		ROS_INFO("Point taken:  x: %f y: %f",potato.x,potato.y);
		last_potato = potato;
	}
	else if(diff(last_potato, potato)>0.1){
		polyLinePoints.push_front(potato);
		ROS_INFO("Point taken:  x: %f y: %f",potato.x,potato.y);
		last_potato = potato;
	}
	//last_potato = potato;
}
*/


int main(int argc,char **argv)
{
	ros::init(argc,argv,"paths");//name of this node
	ros::NodeHandle n;
	ros::Publisher pubseg = n.advertise<beta_nodes::PathSegment>("paths",1);
	ros::Publisher pubPoly = n.advertise<beta_nodes::PathSegment>("polySeg",1);
	ros::Publisher markerPub = n.advertise<visualization_msgs::MarkerArray> ("visualization_marker", 1);
	ros::Subscriber sub = n.subscribe("cmd_corr",1,steeringCallback);
	ros::Subscriber sub1 = n.subscribe("replanning",1,avoidanceCallback);
	ros::Subscriber sub2 = n.subscribe("tapePoint",1,orangeCallback);
	//last_potato.x=999;
	//last_potato.y=999;

	ros::Duration elapsed_time; // define a variable to hold elapsed time
	ros::Rate naptime(Hz); //will perform sleeps to enforce loop rate of "10" Hz
	while (!ros::Time::isValid()) {} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid

	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	ROS_INFO("birthday started as %f", birthday.toSec());

	int segNum = 0; //The ass end of our current PathQueue vector
	beta_nodes::PathSegment curPathSeg; // create an instance of datatype PathSegment
	
	visualization_msgs::Marker marks;
	marks.header.frame_id = "/map";
	marks.header.stamp = ros::Time::now();
	marks.ns = "beta_ns"; //Namespace for these markers. This plus the id form a unique identifier.
	marks.action = visualization_msgs::Marker::ADD; //not many options here
	marks.pose.orientation.w = 1.0;
	marks.id = 0;
	marks.type = visualization_msgs::Marker::POINTS;
	marks.scale.x = marks.scale.y = 0.5;
	marks.color.g = 1.0f;
	marks.color.a = 1.0f;
	
	//dummy population of PathSegment fields
//	curPathSeg.curvature = 3.14;
//	curPathSeg.seg_length=0.0;
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
	/*  Some waypoints used during testing
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
	
	// SEE THE BLUE STUFF ABOVE
	// We ignore that now, but I hate deleting things so it stays for now please

	double DistToGo;

	while (ros::ok()) // do work here
	{
		ros::spinOnce();
		
		//avoidancePatch was used in an older form of our obstacle avoidance, no longer used
		//avoidancePatch.init_point.x += position.x;
		//avoidancePatch.init_point.y += position.y;
		//avoidancePatch.ref_point.x = avoidancePatch.init_point.x + cos(curPathSeg.seg_psi);
		//avoidancePatch.ref_point.y = avoidancePatch.init_point.y + sin(curPathSeg.seg_psi);
		//avoidancePatch.seg_psi = curPathSeg.seg_psi;
		if(true){//pathQueue.size()>0){
			//curPathSeg = pathQueue.back();  This is wrong
			//If we have a poly line point on the curren segment to go to...
			if(polyLinePoints.size()>0){
				//ROS_INFO("We see a point in the queue");
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
				ROS_INFO_STREAM("PUBLISH A");
			}
			//Else, do we have any path segments to go to...
			else if (pathQueue.size() > 0) {
				curPathSeg = pathQueue.front();
				polySeg.ref_point.x = curPathSeg.ref_point.x; 
				polySeg.ref_point.y = curPathSeg.ref_point.y;
				polySeg.init_point.x = position.x;
				polySeg.init_point.y = position.y;
				polySeg.seg_type=1;
				polySeg.seg_psi = atan2((polySeg.ref_point.y-polySeg.init_point.y),(polySeg.ref_point.x-polySeg.init_point.x));
				ROS_INFO_STREAM("PUBLISH B");
			}
			//Else, we have no where else we need to go, don't go anywhere
			else{
				ROS_INFO_STREAM("PUBLISH C");
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
		
		//If we're really close to our next point...
		if(DistToGo<0.1 && curPathSeg.seg_type!=0){
			ROS_INFO("Popped type: %d %d", curPathSeg.seg_type,segNum);
			//If there are points in the poly line queue...
			if(polyLinePoints.size()>0){
				//last_potato = polyLinePoints.back();
				//Clear the point
				polyLinePoints.pop_back();
			}	
		}

		mp.x = curPathSeg.ref_point.x;
		mp.y = curPathSeg.ref_point.y;
		mp.z = 0.5; //floating point lol
		marks.points.push_back(mp);

		//ROS_INFO("Current: %f %f",curPathSeg.ref_point.x,curPathSeg.ref_point.y);
		pubseg.publish(curPathSeg); // publish the path segment
		pubPoly.publish(polySeg);
		markerPub.publish(marks);

		naptime.sleep(); // this will achieve the desired update rate (10Hz)
	}
	return 0; //only get here if node told to shut down ( ros::ok() is false )
}