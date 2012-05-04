#include<ros/ros.h>
#include<cwru_base/cRIOSensors.h>
#include<std_msgs/Bool.h>
#include<math.h>
#include <cwru_base/Pose.h>
#include<geometry_msgs/Twist.h>
#include<beta_nodes/estopMsg.h>

bool estop;

#define HZ 50

//estop call back, check if the robot is e-stoped and store boolean value in the variable "estop"
void estopCallback(const std_msgs::Bool::ConstPtr& est)
{
    if (est->data == true){
        estop=true;  // means motors are ENABLED
        ROS_INFO("Not e-stopped");
    }
    else if (est->data == false){
        estop=false;  // means motors are DISABLED
        ROS_INFO("e-stopped");
    }
}


int main(int argc,char **argv)
{
    ros::init(argc,argv,"estop");//name of this node
    ros::NodeHandle n;
    ros::Publisher publishEstop = n.advertise<beta_nodes::estopMsg>("beta_estop", 1);
    ros::Rate r(HZ);
    beta_nodes::estopMsg m;

    ros::Subscriber sub = n.subscribe("motors_enabled",1,estopCallback);

    while (!ros::Time::isValid()) { }

    while (ros::ok()) {
        // Trigger Callbacks
        ros::spinOnce();

        m.isEstopped = !estop;
        publishEstop.publish(m);
        r.sleep();
    }
    return 0;
}
