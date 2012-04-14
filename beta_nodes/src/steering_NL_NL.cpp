#include<ros/ros.h>
#include<geometry_msgs/Twist.h> //data type for velocities
#include<geometry_msgs/PoseStamped.h> //data type for Pose combined with frame and timestamp
#include<nav_msgs/Odometry.h> //data type for odometry information (see available fields with 'rosmsg show nav_msgs/Odometry')
#include<tf/transform_datatypes.h> // for tf::getYaw
#include<tf/transform_listener.h> // for the TransformListener class that abstracts away a lot of tf
#include<math.h>
#include<cmath>


#include <cwru_base/Pose.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>

using namespace std;



bool existObstacle;
double obstacle_distance = 999999;

double obstacle_x = 0;
double obstacle_y = 0;

double new_xs = 0.0;
double new_ys = 0.0;

double new_xf = 0.0;
double new_yf = 0.0;

double safe_distance = 0.5;

bool finished;



//Note that this initializes to all 0's... so until you get an "initial pose" from the first callback, it's prolly gonna be way wrong for any algorithm to use
nav_msgs::Odometry last_odom;
geometry_msgs::PoseStamped last_map_pose;
tf::TransformListener *tfl;

geometry_msgs::PoseStamped temp;
void odomCallback(const nav_msgs::Odometry::ConstPtr& odom) {
        last_odom = *odom;
        temp.pose = last_odom.pose.pose;
        temp.header = last_odom.header;
        try {
          tfl->transformPose("map", temp, last_map_pose); // given most recent odometry and most recent coord-frame transform, compute
                                                          // estimate of most recent pose in map coordinates..."last_map_pose"
        } catch (tf::TransformException ex) {
          ROS_ERROR("%s", ex.what());
        }
}



void laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan)
{

      if (laserScan->ranges[90]<1.5)
      {
	existObstacle = true;
	obstacle_distance = laserScan->ranges[90];
      }
      else
      {
        existObstacle = false;
        obstacle_distance = 999999;
      }
	

    cout<<endl;
}




int main(int argc,char **argv)
{
	ros::init(argc,argv,"steering_example");//name of this node
	ros::NodeHandle n;
        tfl = new tf::TransformListener();

	//"cmd_vel" is the topic name to publish velocity commands
	//"1" is the buffer size (could use buffer>1 in case network bogs down)
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1);

        ros::Subscriber sub = n.subscribe<nav_msgs::Odometry>("odom", 1, odomCallback); 
    	ros::Subscriber sub2 = n.subscribe("base_scan",1,laserCallback);

	geometry_msgs::Twist vel_object;
	geometry_msgs::Twist cmd_vel;
        geometry_msgs::PoseStamped desired_pose;  // not used in this program...ideally, get by subscription

	while (!ros::Time::isValid()) {ros::spinOnce();} // simulation time sometimes initializes slowly. Wait until ros::Time::now() will be valid, but let any callbacks happen
        while (!tfl->canTransform("map", "odom", ros::Time::now())) {ros::spinOnce();} // wait until there is transform data available before starting our controller loop
	//ros::Duration run_duration(3.0); // specify desired duration of this command segment to be 3 seconds
	ros::Duration elapsed_time; // define a variable to hold elapsed time
	ros::Rate naptime(10); //will perform sleeps to enforce loop rate of "10" Hz
	ros::Time birthday= ros::Time::now(); // get the current time, which defines our start time, called "birthday"
	ROS_INFO("birthday started as %f", birthday.toSec());

	double xf, yf, xs, ys; // Final desired x,y values for the current leg of the move

	vel_object.linear.x = 0.0; // Initial velocity
	vel_object.angular.z = 0.0;
	
	double dtheta, offset;
 	double desired_heading,current_heading; //desired and actual robot heading
	double x_current,y_current; // current x,y position of robot in map coords
	double tx,ty,nx,ny;  //path tangent and normal vector components
	double xrs,yrs; // x and y coords of robot relative to start (xs,ys)
	
	
	// tune these values, Kd and Ktheta, for steering
	double Kd =0.5;
	double Ktheta = 1.0;
	
	double dt = .05;
	double pi = 3.14159;
        // instead of subscribing to path segments, for this simple example, hard-code a single line
	xs = 5.0; // start point
	ys =12.25;

	xf = -3.3; // end point (or a second point, forward, on the line)
	yf = 20.6;
	desired_heading = atan2(yf-ys,xf-xs);
	ROS_INFO("desired heading: %f",desired_heading);
	
	while (ros::ok()) // do work here
	{
		ros::spinOnce(); // allow any subscriber callbacks that have been queued up to fire, but don't spin infinitely
		ros::Time current_time = ros::Time::now();
		elapsed_time= current_time-birthday;
                
                
		ROS_INFO("\n\n");
		ROS_INFO("time from birthday: %f", (last_map_pose.header.stamp - birthday).toSec());


		current_heading = tf::getYaw(last_map_pose.pose.orientation);
		//corresponding tangent and normal vector components of reference path (straight-line example)
		tx =cos(desired_heading);
		ty = sin(desired_heading);
		nx = -ty;
		ny = tx;
		
		//ROS_INFO("desired heading: %f, current heading: %f",desired_heading, current_heading);

		

		// error in heading
		dtheta = desired_heading-current_heading;
		if (dtheta>pi)   // watch out for wrap-around
			dtheta=dtheta-2*pi;
		if (dtheta<-3.14159)	//why not just -pi?
                        dtheta=dtheta+2*pi;

                //compute offset error:
		x_current = last_map_pose.pose.position.x;
		y_current = last_map_pose.pose.position.y;

		//ROS_INFO("x_robot: %f, y_robot: %f",x_current, y_current);



		finished = true;
		//compute obstacle coordinates
		if(existObstacle == true)
		{
		  finished = false;
		  
		  //ROS_INFO("Obstacle Distance: %f ", obstacle_distance);

                  obstacle_x = x_current+obstacle_distance*cos(current_heading);
                  obstacle_y = y_current+obstacle_distance*sin(current_heading); 			
			
		  //ROS_INFO("Obstacle_x: %f,  Obstacle_y: %f", obstacle_x, obstacle_y);

		  double norm_current_heading = current_heading+0.5*pi;

		  if (norm_current_heading>pi)   // watch out for wrap-around
		  {
			norm_current_heading =norm_current_heading-2*pi;
		  }
	
			
		  new_xs = obstacle_x + safe_distance*cos(norm_current_heading);
		  new_ys = obstacle_y + safe_distance*sin(norm_current_heading);

		  //ROS_INFO("new_xs: %f,  new_ys: %f", new_xs, new_ys);
		
			
		  new_xf = new_xs + 3*safe_distance*cos(current_heading);
                  new_yf = new_ys + 3*safe_distance*sin(current_heading); 	
		  
		}


		while(finished == false)
		{
			ROS_INFO("Obstacle mode");
			desired_heading = atan2(new_yf-new_ys,new_xf-new_xs);

			ros::spinOnce(); 
			
			current_heading = tf::getYaw(last_map_pose.pose.orientation);
			//corresponding tangent and normal vector components of reference path (straight-line example)
			tx =cos(desired_heading);
			ty = sin(desired_heading);
			nx = -ty;
			ny = tx;
		

			// error in heading
			dtheta = desired_heading-current_heading;
			if (dtheta>pi)   // watch out for wrap-around
				dtheta=dtheta-2*pi;
			if (dtheta<-3.14159)
                  	      dtheta=dtheta+2*pi;

               		//compute offset error:
			x_current = last_map_pose.pose.position.x;
			y_current = last_map_pose.pose.position.y;

			ROS_INFO("x_robot: %f, y_robot: %f",x_current, y_current);


			if(abs(x_current-new_xf)<0.3 && abs(y_current-new_yf)<0.3)
			{finished = true;}
			else
			{finished = false;}

			
			//vector from start point to current robot point
			xrs = x_current-new_xs;
			yrs = y_current-new_ys;

			// dot this vector with path normal vector to get the offset (works for line segments)
			offset = xrs*nx+yrs*ny;



			double d_threshold = 0.5;
			double psi_des;

			if(offset > d_threshold)
			{
				psi_des=desired_heading-0.5*pi;
			}
			else if(offset < -d_threshold)
			{
				psi_des=desired_heading+0.5*pi;
			}
			else
			{
				psi_des=desired_heading-(pi*0.5)*offset/d_threshold; 
			}
			double psi_err = current_heading-psi_des;
			if(psi_err > pi)
			{
				psi_err = psi_err-2*pi;
			}
			if(psi_err < -pi)
			{
				psi_err = psi_err+2*pi;
			}




			double K_omega = 2.0; 
			double omega_sat = 2.0; 

			double omega_cmd = -K_omega*psi_err;

			if(omega_cmd > omega_sat)
			{
				omega_cmd = omega_sat;
			}
			if(omega_cmd < -omega_sat)
			{
				omega_cmd = -omega_sat;
			}

			// steering control law
			cmd_vel.angular.z = omega_cmd; // simple, linear controller; can do better
			cmd_vel.linear.x=0.2; //command constant fwd vel
		
		
			//ROS_INFO("Offset=%f, psi_err=%f, cmd omega=%f",offset,psi_err,cmd_vel.angular.z);
			
		
			pub.publish(cmd_vel); // Publish the velocity (incorporating feedback)
		
			naptime.sleep(); //Sleep, thus enforcing the desired update rate

		}

		//vector from start point to current robot point
		xrs = x_current-xs;
		yrs = y_current-ys;

		// dot this vector with path normal vector to get the offset (works for line segments)
		offset = xrs*nx+yrs*ny;



		double d_threshold = 1.0;
		double psi_des;

		if(offset > d_threshold)
		{
			psi_des=desired_heading-0.5*pi;
		}
		else if(offset < -d_threshold)
		{
			psi_des=desired_heading+0.5*pi;
		}
		else
		{
			psi_des=desired_heading-(pi*0.5)*offset/d_threshold; 
		}
		double psi_err = current_heading-psi_des;
		if(psi_err > pi)
		{
			psi_err = psi_err-2*pi;
		}
		if(psi_err < -pi)
		{
			psi_err = psi_err+2*pi;
		}




		double K_omega = 2.0; 
		double omega_sat = 2.0; 

		double omega_cmd = -K_omega*psi_err;

		if(omega_cmd > omega_sat)
		{
			omega_cmd = omega_sat;
		}
		if(omega_cmd < -omega_sat)
		{
			omega_cmd = -omega_sat;
		}

		// steering control law
		cmd_vel.angular.z = omega_cmd; // simple, linear controller; can do better
		cmd_vel.linear.x=0.5; //command constant fwd vel
		
		
		//ROS_INFO("Offset=%f, psi_err=%f, cmd omega=%f",offset,psi_err,cmd_vel.angular.z);
		
		
		pub.publish(cmd_vel); // Publish the velocity (incorporating feedback)
		
		naptime.sleep(); //Sleep, thus enforcing the desired update rate
	}// while
	
  delete tfl;
	return 0; // this code will only get here if this node was told to shut down
}// main









