//Publish paths from some source, maybe 

//TODO: add ability to push some new segment to the front of the queue
//want to conert waypoints to path segments 
#include<ros/ros.h>
#include<geometry_msgs/Twist.h> //data type for velocities
#include<beta_nodes/PathSegment.h>
#include<tf/transform_datatypes.h> //for tf::getYaw and create quaternion
#include <beta_nodes/steeringMsg.h>
#include "Path.h"

#define Hz 50
#define LINE 1
#define ARC 2
#define SPIN 3

Vector position;

void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
}
/*
const double waypoints =  //[map x, map y, map phi]
	[[8.42, 15.09, -137.16], //start
	 [5.27, 11.99, -133.33], //lab door
	 [5.27, 11.99, 134.99], //after 90deg turn
	 [0.02, 17.14, 134.99],  //halfway down hall
	 [-3.25, 20.71, 137.86], //at "T"
	 [-3.25, 20.71, 40.46], //after second spin
	 [1.00, 24.75, 40.46]]; //end
*/
int main(int argc,char **argv)
{
	ros::init(argc,argv,"paths");//name of this node
	ros::NodeHandle n;
	ros::Publisher pubseg = n.advertise<beta_nodes::PathSegment>("paths",1);
	ros::Subscriber sub = n.subscribe("cmd_corr",1,steeringCallback);

	ros::Duration elapsed_time; // define a variable to hold elapsed time
	ros::Rate naptime(Hz); //will perform sleeps to enforce loop rate of "10" Hz
	while (!ros::Time::isValid()) {} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid

	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	ROS_INFO("birthday started as %f", birthday.toSec());


	beta_nodes::PathSegment curPathSeg; // create an instance of datatype PathSegment
	//dummy population of PathSegment fields
//	curPathSeg.curvature = 3.14;
//	curPathSeg.seg_length=0.0;
	curPathSeg.ref_point.x=-0.4;
	curPathSeg.ref_point.y=0.4;
//	curPathSeg.seg_number=123;
	curPathSeg.seg_type=1;
//	curPathSeg.init_tan_angle=tf::createQuaternionMsgFromYaw(1.23);
//	curPathSeg.max_speeds.linear.x=3.45;
//	curPathSeg.max_speeds.angular.z=1.23;
//	curPathSeg.accel_limit=4.56;
//	curPathSeg.decel_limit=5.67;

	double DistToGo;

	while (ros::ok()) // do work here
	{
		ros::spinOnce();
//		elapsed_time= ros::Time::now()-birthday;
//		ROS_INFO("birthday is %f", birthday.toSec());
//		ROS_INFO("elapsed time is %f", elapsed_time.toSec());
		DistToGo = sqrt(pow(curPathSeg.ref_point.x-position.x,2)+pow(curPathSeg.ref_point.y-position.y,2));
//		curPathSeg.seg_length= elapsed_time.toSec();
		ROS_INFO("%f - %f + %f - %f = %f",curPathSeg.ref_point.x,position.x,curPathSeg.ref_point.y,position.y,DistToGo);
		if(DistToGo<0.1){
			curPathSeg.seg_type = 0;
		}
		pubseg.publish(curPathSeg); // publish the path segment



		naptime.sleep(); // this will achieve the desired update rate (10Hz)
	}
	return 0; //only get here if node told to shut down ( ros::ok() is false )
}
