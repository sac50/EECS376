#include<ros/ros.h>
#include<cwru_base/cRIOSensors.h>
#include<std_msgs/Bool.h>
#include<math.h>
#include <cwru_base/Pose.h>
#include<geometry_msgs/PoseStamped.h> //data type for Pose combined with frame and timestamp
#include<nav_msgs/Odometry.h> //data type for odometry information (see available fields with 'rosmsg show nav_msgs/Odometry')
#include<tf/transform_datatypes.h> // for tf::getYaw
#include<tf/transform_listener.h>
#include<geometry_msgs/Twist.h> //data type for velocities
#include "Path.h"
#include <beta_nodes/steeringMsg.h>
#include <beta_nodes/velocityMsg.h>
#include <beta_nodes/obstacle.h>
#include <beta_nodes/vPassBack.h>
#include <beta_nodes/PathSegment.h>
#include <beta_nodes/estopMsg.h>
//#include <beta_nodes/pathMsg.h>

#define ESP = 6
#define OBS = 5
#define OFF = 4
#define GEN = 2

int priority=0;
double HZ = 50;
double dt = 1/HZ;
beta_nodes::velocityMsg velocityMsg;
Vector position;
double omega_cmd;
bool estop=false;
bool recoveringFromEstop=false;
//beta_nodes::steeringMsg steeringMsg;
//beta_nodes::obstacle obstacle;
//beta_nodes::estopMsg estopMsg;
//beta_nodes::pathMsg pathMsg;

void obstructionsCallback(const beta_nodes::obstacle::ConstPtr& obs) {

}

void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
	omega_cmd = str->omega_cmd;
	//ROS_INFO("Got Position");
}

void velocityCallback(const beta_nodes::velocityMsg::ConstPtr& vel){
	velocityMsg.velocity = vel->velocity;
	ROS_INFO("Velocity: %f",vel->velocity);
}


void estopCallback(const beta_nodes::estopMsg::ConstPtr& esp){
	if(estop!=esp->isEstopped && !recoveringFromEstop){
		estop=esp->isEstopped;
	}
	else if(estop!=esp->isEstopped){
		recoveringFromEstop=true;
	}
}


/*
void pathQueueCallback(const beta_nodes::pathMsg::ConstPtr& pth){

}
*/

void holdingPattern(double time, ros::Publisher vel_pub, ros::Publisher passback_pub){
	double t=0;
	ros::Rate naptime(HZ);
	geometry_msgs::Twist vel_object;
	beta_nodes::vPassBack vPassBack;
	while(ros::ok() && t<time){
		t=t+dt;	
		vel_object.linear.x = 0.0;
		vel_object.angular.z = 0.0;
//		ROS_INFO("standing %f %f", t, dt);
		vel_pub.publish(vel_object);  // this action causes the commands in vel_object to be published
		vPassBack.vPast = 0;
		vPassBack.posX = position.x;
		vPassBack.posY = position.y;
		passback_pub.publish(vPassBack);
		
		naptime.sleep();
	}
	return;
}

int main(int argc, char** argv) {
	ros::init(argc,argv,"MasterController");//name of this node
	ros::NodeHandle n;
	ros::Rate naptime(HZ);
	ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1);
	ros::Publisher passback_pub = n.advertise<beta_nodes::vPassBack>("vPast",1);
	ros::Subscriber sub = n.subscribe("velocityMsg",1,velocityCallback);
	ros::Subscriber sub1 = n.subscribe("cmd_corr",1,steeringCallback);
	//ros::Subscriber sub2 = n.subscribe("obstacle", 1,obstacleCallback);
	ros::Subscriber sub3 = n.subscribe("beta_estop", 1,estopCallback);
	//ros::Subscriber sub4 = n.subscribe("pathGen", 1,pathQueueCallback);

	//"cmd_vel" is the topic name to publish velocity commands
	//"1" is the buffer size (could use buffer>1 in case network bogs down)

	while (!ros::Time::isValid()) {} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid
	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	ROS_INFO("birthday started as %f", birthday.toSec());
	
	geometry_msgs::Twist vel_object;
	beta_nodes::vPassBack vPassBack;
	
	while (ros::ok()){
		if(estop){
			ros::spinOnce();
			vel_object.linear.x = 0;
			vel_object.angular.z = 0;
			vel_pub.publish(vel_object);
			vPassBack.vPast = 0;
			vPassBack.posX = position.x;
			vPassBack.posY = position.y;
			passback_pub.publish(vPassBack);
		}
		else{
			if(recoveringFromEstop){
				holdingPattern(1,vel_pub,passback_pub);
			}
			else{
				ros::spinOnce();
				vel_object.linear.x = velocityMsg.velocity;
				vel_object.angular.z = omega_cmd;
				vel_pub.publish(vel_object);
				vPassBack.vPast = velocityMsg.velocity;
				vPassBack.posX = position.x;
				vPassBack.posY = position.y;
				passback_pub.publish(vPassBack);
			}
		}
		
		naptime.sleep();
	}
	
}

