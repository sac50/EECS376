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

#define HALF_PI 1.6079633
#define CW -1.0
#define HZ 10
#define CCW 1.0
#define omega_max 1.0
#define alpha_max 0.5
#define LINEAR_PATH 1
#define SPIN_IN_PLACE 2
#define ARC_PATH 3

double velocityMax = 0.75;  // Default Speedlimit.  Should be set by path class
double accelerationMax = 0.25; //  Default Acceleration.  Should be set by the path class
double segmentDistanceLeft = 0.0;
bool braking=false;
double time1 = 0.0;
double dt = 0.1;


nav_msgs::Odometry lastOdometry;
tf::TransformListener *transformListener;
geometry_msgs::PoseStamped lastMapPose;

double getPathDistanceLeft(Path path);
double getVelocity(double velocityPast, double velocityCommand, double segmentDistanceDone, double segmentType, Path path);
using namespace std;

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
double getVelocity(double velocityPast, double velocityCommand, double segmentDistanceDone, double segmentType, Path path) {
	double velocityScheduled;
	geometry_msgs::Twist velocityCommandPublish;
	// Dynamically defined breaking distance from commanded velocity
	double brakingDistance = (velocityCommand/accelerationMax) * (velocityCommand/2);
	time1 = time1 + dt;
	segmentDistanceDone += ((velocityPast + velocityCommand)/2)*dt;
	// continue on line 200 on command publisher
	double pathDistanceLeft = getPathDistanceLeft(path);
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

double getPathDistanceLeft(Path path) {
	double pathDistanceLeft = sqrt(abs(pow(path.getEnd().X()-lastMapPose.pose.position.x,2)+pow(path.getEnd().Y()-lastMapPose.pose.position.y,2)));
	return pathDistanceLeft;
}

int main(int argc, char** argv) {
	// initialize node
	ros::init(argc, argv, "velocity"); 
	ros::NodeHandle nodeHandle;
	ros::Publisher publishVelocity = nodeHandle.advertise<beta_nodes::velocityMsg>("velocityMsg", 1);
	ros::Rate r(HZ);	
	beta_nodes::velocityMsg velocityMsg;	
	// Subscriber to pose ?
	// Subscriber to steering

	/* Simulation time sometimes initializes slowly. 
	 * Wait until ros::Time::now() will be valid 
         */
	while (!ros::Time::isValid()) { }

	while (ros::ok()) {
		// Trigger Callbacks
		ros::spinOnce();
		// Callbacks set values
		// Get VelocityPath
		
		// Get VelocityCommand

		// Get Segment Distance Done

		// Get Segment Type

		// Get Path
	//	geometry_msgs::Twist velocity = getVelocity(velocityPast, velocityCommand, segmentDistanceDone, segmentType, path);

		velocityMsg.velocity = 1;
		publishVelocity.publish(velocityMsg);

		r.sleep();
	}
	return 0;	
}	
