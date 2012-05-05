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
#include "Path.h" //Our helper library
#include <beta_nodes/steeringMsg.h>
#include <beta_nodes/PathSegment.h>

//Global values used throughout the steering algorithm
const double pi = 3.141592;
//Threshold distance from which to make perpendicular approach to path
double d_threshold = 1.0;
// omega = 1.5 omega sat 0.5
double Kd=0,K_omega=1.5,omega_sat=0.5;
//Update frequency
double nap = 50.0;
double dt = 1.0/nap;

using namespace std;

//Variables to track most recent odometry and map pose
nav_msgs::Odometry last_odom;
geometry_msgs::PoseStamped last_map_pose;
//geometry_msgs::PoseStamped old_map_pose;
tf::TransformListener *tfl;
Path path;
//Vector ignore = path.n_hatCalc(); Used only during some testing
geometry_msgs::PoseStamped temp;


//Odometry Callback
//Gets the robots current map position for use in steering calculations
void odomCallback(const nav_msgs::Odometry::ConstPtr& odom) {
	//old_map_pose=last_map_pose;
		//ROS_INFO_STREAM("ODOM CALLBACK");
		last_odom = *odom;
        temp.pose = last_odom.pose.pose;
        temp.header = last_odom.header;
        temp.header.frame_id = "odom";
        
        try {
          tfl->transformPose("map", temp, last_map_pose); // given most recent odometry and most recent coord-frame transform, compute
                                                          // estimate of most recent pose in map coordinates..."last_map_pose"
		ROS_INFO("Postion: X: %f Y: %f Z: %f",last_map_pose.pose.position.x, last_map_pose.pose.position.y, last_map_pose.pose.position.z);
        } catch (tf::TransformException ex) {
          ROS_ERROR("%s", ex.what());
        }
}

//Path Callback
//Gets the current path segment and initializes values used only during steering calculations
void pathQueueCallback(const beta_nodes::PathSegment::ConstPtr& pth){
	if(pth->seg_type == 0){
		path.type = 0;
	}
	path.start.x = pth->init_point.x;
	path.start.y = pth->init_point.y;
	path.end.x = pth->ref_point.x;
	path.end.y = pth->ref_point.y;
	path.type = pth->seg_type;
	path.seg_psi = pth->seg_psi;
	path.t_hat.x = cos(path.seg_psi);
	path.t_hat.y = sin(path.seg_psi);
	path.n_hatCalc();
}

int main(int argc,char **argv){
	ros::init(argc,argv,"steering");//name of this node
	ros::NodeHandle n;
	tfl = new tf::TransformListener();
	ros::Publisher pub = n.advertise<beta_nodes::steeringMsg>("cmd_corr",1);
	ros::Subscriber sub = n.subscribe<nav_msgs::Odometry>("odom", 1, odomCallback);
	ros::Subscriber sub1 = n.subscribe("paths", 1,pathQueueCallback);
	
	while (!ros::Time::isValid()) {} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid
	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	while (!tfl->canTransform("map", "odom", ros::Time::now())) { ROS_INFO_STREAM("WAITING FOR ODOM"); ros::spinOnce();}
	
	//while (!tfl->canTransform("map", "camera_link", ros::Time::now())) {ROS_INFO_STREAM("NO"); ros::spinOnce();}
	
	ROS_INFO("birthday started as %f", birthday.toSec());
	ros::Rate naptime(nap);
	
	beta_nodes::steeringMsg steeringMsg;
	
	Vector t1,t2;
	//t1.x=-2.48;
	//t1.y=2.24;
	//t2.x=-0.4;
	//t2.y=0.4;
	path.init(path.start,path.end,1);
	
	double psidot,xdot,ydot,psi_des,psi_err,psi_robot,d,omega_cmd, time=0;
	Vector xy;
	
	//Steering algorithm loop
	while (ros::ok()){
		ros::spinOnce();
		if(path.type != 0){
			psi_robot=tf::getYaw(last_map_pose.pose.orientation);
			xy.set(last_map_pose.pose.position.x,last_map_pose.pose.position.y);
			d = path.d_off(xy);
			if (d> d_threshold){ //%if far to the left of the path, heading should point toward the path
				psi_des = path.seg_psi-pi/2; //%this heading is perpendicular to the path, pointing towards the path
				steeringMsg.priority_approach = true;
			}
			else if (d< -d_threshold){ //%same thing if offset too far to the right--point towards path
				psi_des = path.seg_psi+pi/2;
				steeringMsg.priority_approach = true;
			}
			else{ //%if offset is not large, make the heading gradually parallel to the path;
				psi_des = path.seg_psi-(pi/2)*d/d_threshold;  //% heading offset proportional to displacement offset
				steeringMsg.priority_approach = false;
			}
		    
			psi_err = psi_robot-psi_des; //%compare the current robot heading to the scheduled heading
			if (psi_err > pi)  //%express heading error in range -pi to pi
				psi_err = psi_err-2*pi;
			if (psi_err < -pi)
				psi_err = psi_err+2*pi;
			//ROS_INFO("Des: %f Rob: %f Err: %f",path.seg_psi,psi_robot,psi_err);
			//%feedback to coerce robot heading to conform to scheduled heading
			omega_cmd = -K_omega*psi_err;  //%linear control law-> omega_cmd
			//%limit the spin command to the legal range
			if (omega_cmd > omega_sat)
				omega_cmd = omega_sat;
			else if (omega_cmd < -omega_sat)
				omega_cmd = -omega_sat;
		    
			//%differential robot kinematics:
	
			psidot = omega_cmd;
			xdot = cos(psi_robot);
			ydot = sin(psi_robot);
		    
			//%Euler one-step integration:
			psi_robot = psi_robot+psidot*dt;
			//%force heading into range -pi to pi
			if (psi_robot >pi)
				psi_robot = psi_robot-2*pi;
			if (psi_robot< -pi)
				psi_robot = psi_robot+2*pi;
			//%Euler one-step for x and y updates:
			//xy_robot_coords = xy_robot_coords + [xdot;ydot]*dt;
		
			steeringMsg.omega_cmd = omega_cmd;
			steeringMsg.posX = last_map_pose.pose.position.x;
			steeringMsg.posY = last_map_pose.pose.position.y;
			steeringMsg.heading = psi_robot;
			//ROS_INFO("Postion: X: %f Y: %f",last_map_pose.pose.position.x, last_map_pose.pose.position.y);
			pub.publish(steeringMsg);
		}
		else{
			steeringMsg.omega_cmd = 0;
			steeringMsg.posX = last_map_pose.pose.position.x;
			steeringMsg.posY = last_map_pose.pose.position.y;
			steeringMsg.heading = 0.0;
			ROS_INFO("Postion: X: %f Y: %f",last_map_pose.pose.position.x, last_map_pose.pose.position.y);
			pub.publish(steeringMsg);
		}
		time=time+dt;
		naptime.sleep();
	}	
}