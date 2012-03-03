#include<ros/ros.h>
#include<cwru_base/cRIOSensors.h>
#include<std_msgs/Bool.h>
#include<math.h>
#include <cwru_base/Pose.h>
#include<geometry_msgs/Twist.h>
#include<geometry_msgs/PoseStamped.h> //data type for Pose combined with frame and timestamp
#include<nav_msgs/Odometry.h> //data type for odometry information (see available fields with 'rosmsg show nav_msgs/Odometry')
#include<tf/transform_datatypes.h> // for tf::getYaw
#include<tf/transform_listener.h>
#include "Path.h"

const double pi = 3.141592;

nav_msgs::Odometry last_odom;
geometry_msgs::PoseStamped last_map_pose;
tf::TransformListener *tfl;
Path segment;

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

Path decomposeMsg(steering::Path pubP){
	if(pubP.type == 1){	
		Vector s(pubP.x0,pubP.y0);
		Vector e(pubP.x1,pubP.y1);
		Path p;
		p.init(s,e,pubP.type);
		return p;
	}
	else if(pubP.type == 2){
		Path p;
		p.init(pubP.psiS,pubP.psiF,pubP.type);
		return p;
	}

	return NULL;
}

void pathCallback(const steering::Path::ConstPtr& pubP){
	segment = decomposeMsg(pubP);
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"correction_publisher");//name of this node
	ros::NodeHandle n;
        tfl = new tf::TransformListener();
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1);
        ros::Subscriber sub = n.subscribe<nav_msgs::Odometry>("odom", 1, odomCallback);
        //ros::Subscriber pSub = n.subscribe<steering::Path>("SegPath",1,pathCallback);
	//"cmd_vel" is the topic name to publish velocity commands
	//"1" is the buffer size (could use buffer>1 in case network bogs down)

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


}
//%apply nonlinear steering algorithm to nonlinear robot kinematics

//%steering simulation, 2nd order
//%assumes can command (and achieve) an arbitrary spin-rate command, omega,
//%instantaneously, although limited to max (saturation) spin rate commands
//%Assume constant speed, v

//%Assume desired direction of motion is a line at angle psi_des passing
//%through point x_start:
double x0,y0;//xy_start_coords = [1;0];
//%choose direction for desired path segment
double psi_path_seg = pi/4;// %45-deg angle
Vector t_hat(cos(psi_path_seg),sin(psi_path_seg));// %vector parallel to direction of desired path
//%nhat is vector normal to desired direction of motion; used for computation
//%of offset; n_hat = Rot_about_z(pi/2)*t_hat
Vector n_hat = [0 -1; 1 0]*t_hat;

//%Controller should null out displacement from desired path and should null out
//%heading error; displacement is measured positive to the "left" when facing
//%along the path in the desired direction of travel

//%control parameters:
double d_threshold = 1.0; //%decide where to begin transition from perpendicular approach to sloped convergence
double K_omega = 30.0; //% gain for correcting heading...experiment with this value
double omega_sat = 2.0; //%max rads/sec

//%simulate robot motion w/ x_vec defined as [x;y] and heading is psi
//%choose initial conditions: x,y,psi:
double x0 = 0;
double y0 = 1;
double psi0 = 0;

//%specify forward speed, v:
double v = 1; //%1m/sec;  note that should change gains if change speed

//%create some arrays to store simulation results
d_history = []; 
psi_history = [];
psi_des_history = [];
t_history = [];
u_history= []; //%save history of omega commands as well
x_history = [];
y_history = [];
xy_robot_coords = [x0;y0]; //% initialize variables
psi_robot = psi0;
x_dot = [0;0]; //%compute these terms to integrate differential equations
omega_cmd = 0;
t=0; //%time starts at zero
dt = 0.01; //%choose time step for simulation
t_final = 5; //%choose simulation duration
for t = 0:dt:t_final
    //%compute appropriate heading as a function of offset:
    
    //%compute the offset error:
    d = (xy_robot_coords-xy_start_coords)'*n_hat;
    if d> d_threshold //%if far to the left of the path, heading should point toward the path
        psi_des = psi_path_seg-pi/2; //%this heading is perpendicular to the path, pointing towards the path
    elseif d< -d_threshold //%same thing if offset too far to the right--point towards path
        psi_des = psi_path_seg+pi/2;
    else //%if offset is not large, make the heading gradually parallel to the path;
        psi_des = psi_path_seg-(pi/2)*d/d_threshold;  //% heading offset proportional to displacement offset
    end
    
    psi_err = psi_robot-psi_des; //%compare the current robot heading to the scheduled heading
    if psi_err > pi  //%express heading error in range -pi to pi
        psi_err = psi_err-2*pi;
    end
    if psi_err < -pi
        psi_err = psi_err+2*pi
    end
    
    //%feedback to coerce robot heading to conform to scheduled heading
    omega_cmd = -K_omega*psi_err;  %linear control law-> omega_cmd
    //%limit the spin command to the legal range
    if omega_cmd > omega_sat
        omega_cmd = omega_sat
    elseif omega_cmd < -omega_sat
        omega_cmd = -omega_sat
    end
    
    //%store incremental results for post plotting
    t_history=[t_history,t];
    d_history = [d_history,d];
    x_history = [x_history,xy_robot_coords(1)];
    y_history = [y_history,xy_robot_coords(2)];
    psi_history = [psi_history,psi_robot];
    u_history = [u_history,omega_cmd];
    psi_des_history=[psi_des_history,psi_des];
  
    //%differential robot kinematics:
    psidot = omega_cmd;
    xdot = v*cos(psi_robot);
    ydot = v*sin(psi_robot);
    
    //%Euler one-step integration:
    psi_robot = psi_robot+psidot*dt;
    //%force heading into range -pi to pi
    if psi_robot >pi
        psi_robot = psi_robot-2*pi;
    end
    if psi_robot< -pi
        psi_robot = psi_robot+2*pi;
    end
    //%Euler one-step for x and y updates:
    xy_robot_coords = xy_robot_coords + [xdot;ydot]*dt;

end
figure(1)
plot(t_history,d_history)
xlabel('time (sec)')
ylabel('offset (m)')
title('offset response')
figure(2)
plot(t_history,psi_history,'b',t_history,psi_des_history,'r')
xlabel('time (sec)')
ylabel('psi (rad)')
title('heading response: des (r) and act (b)')
figure(3)
plot(t_history,u_history)
xlabel('time (sec)')
ylabel('omega command (rad/sec)')
title('control effort')
figure(4)
//%plot the desired path...
xdes_vec = [xy_start_coords(1),xy_start_coords(1)+t_hat(1)*3];
ydes_vec = [xy_start_coords(2),xy_start_coords(2)+t_hat(2)*3];
plot(xdes_vec,ydes_vec,'b',x_history,y_history,'r')
xlabel('x axis')
ylabel('y axis')
title('desired (blue) and actual (red) path')
