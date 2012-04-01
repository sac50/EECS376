#include <ros/ros.h>
#include <cwru_base/cRIOSensors.h>
#include <std_msgs/Bool.h>
#include <math.h>
#include <cwru_base/Pose.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include "Path.h"
#include <beta_nodes/velocityMsg.h>
#include <beta_nodes/vPassBack.h>
#include <beta_nodes/PathSegment.h>

#define HALF_PI 1.6079633
#define CW -1.0
#define HZ 10
#define CCW 1.0
#define omega_max 1.0
#define alpha_max 0.5
#define LINEAR_PATH 1
#define SPIN_IN_PLACE 2
#define ARC_PATH 3

double velocityMax = 0.50;  // Default Speedlimit.  Should be set by path class
double accelerationMax = 0.25; //  Default Acceleration.  Should be set by the path class
double segmentDistanceLeft = 0.0;
bool braking=false;
double time1 = 0.0;
double dt = 0.02;
// Get Path
Path path;
double velocityPast = 0;
double velocityCommand = 0;
double segmentDistanceDone = 0;
double segmentType = 0;
double posX = 0;
double posY = 0;

nav_msgs::Odometry lastOdometry;
tf::TransformListener *transformListener;
geometry_msgs::PoseStamped lastMapPose;

double getPathDistanceLeft();
double getVelocity();
using namespace std;

void masterCallback(const beta_nodes::vPassBack::ConstPtr& p) {
	//path = p.path;
	//segmentType = p.segmentType;
	velocityPast = p->vPast;
	posX = p->posX;
	posY = p->posY;
}

void pathQueueCallback(const beta_nodes::PathSegment::ConstPtr& pth){
	ROS_INFO("%d",pth->seg_type);
	if(pth->seg_type == 0){
		path.type = 0;
	}
	path.end.x = pth->ref_point.x;
	path.end.y = pth->ref_point.y;
	path.type = pth->seg_type;
}


/* Compute the min between two numbers */
double min (double a, double b) {
	if (a < b) { return a; }
	return b;
}

/* Compute the max between two numbers */
double max (double a, double b) {
	if (a > b) { return a; }
	return b;
}

/* Get the Velocity that should be published */
double getVelocity() {
	double velocityScheduled;
	geometry_msgs::Twist velocityCommandPublish;
	// Dynamically defined breaking distance from commanded velocity
	double brakingDistance = (velocityCommand/accelerationMax) * (velocityCommand/2);
	time1 = time1 + dt;
	segmentDistanceDone += ((velocityPast + velocityCommand)/2)*dt;
	velocityPast = velocityCommand;
	// continue on line 200 on command publisher
	double pathDistanceLeft = getPathDistanceLeft();
	//ROS_INFO("Path Distance Left: %f", pathDistanceLeft);
	//ROS_INFO("SegmentDistance Done: %f", segmentDistanceDone);
	//ROS_INFO("Path Distance Left > breaking distance");
	ROS_INFO("%f > %f", pathDistanceLeft, brakingDistance);
	if (pathDistanceLeft > brakingDistance && !braking) {
		velocityCommand = velocityCommand + accelerationMax*dt;
		if (velocityCommand > velocityMax) {
			velocityCommand = velocityMax;
		}
	}
	else {
		// BRAKE
		braking = true;
		double tempDistance = 2*(pathDistanceLeft)*accelerationMax;
		// No distance left to brake.  Schedule 0 velocity
		if (tempDistance < 0) { 
			velocityScheduled = 0.0;
		} 
		else {
			velocityScheduled = sqrt(tempDistance);
		}

		if (velocityCommand > velocityScheduled) {
			double velocityTest = velocityCommand -1.2*accelerationMax*dt;
			velocityCommand = max(velocityTest, velocityScheduled);
		}
	}
	
	return velocityCommand;
}

double getPathDistanceLeft() {
	double pathDistanceLeft = sqrt(pow(path.getEnd().X()-posX,2)+pow(path.getEnd().Y()-posY,2));
	return pathDistanceLeft;
}

int main(int argc, char** argv) {
	// initialize node
	ros::init(argc, argv, "velocity"); 
	ros::NodeHandle nodeHandle;
	ros::Publisher publishVelocity = nodeHandle.advertise<beta_nodes::velocityMsg>("velocityMsg", 1);
	ros::Subscriber sub = nodeHandle.subscribe("vPast",1, masterCallback);
	ros::Subscriber sub1 = nodeHandle.subscribe("paths", 1,pathQueueCallback);
	ros::Rate r(HZ);	
	beta_nodes::velocityMsg velocityMsg;	
	// Subscriber to pose ?
	// Subscriber to steering

	/* Simulation time sometimes initializes slowly. 
	 * Wait until ros::Time::now() will be valid 
         */
	while (!ros::Time::isValid()) { }
	
	// Get Path
	//Vector t1,t2;
	//t1.x=-2.48;
	//t1.y=2.24;
	//t2.x=-0.4;
	//t2.y=0.4;
	//path.init(t1,t2,1);
	//Vector ignore = path.n_hatCalc();

	while (ros::ok()) {
		// Trigger Callbacks
		ros::spinOnce();

		if(path.type != 0){
			velocityMsg.velocity = getVelocity();
			ROS_INFO("V: %d", path.type);
			publishVelocity.publish(velocityMsg);
		}
		else{
			velocityMsg.velocity=0;
			ROS_INFO("V: %d", path.type);
			publishVelocity.publish(velocityMsg);
		}
		r.sleep();
	}
	return 0;	
}	
