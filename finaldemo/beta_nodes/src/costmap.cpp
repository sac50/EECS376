#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d_publisher.h>
#include <base_local_planner/trajectory_planner_ros.h>
#include <navfn/navfn_ros.h>

//ALL CREDIT GOES TO ALPHAS

int main(int argc, char** argv){

	//initialize ROS
	ros::init(argc, argv, "costmap");

	//create a Transform Listener
	tf::TransformListener tf(ros::Duration(10));

	//we'll need a node handle
	ros::NodeHandle n;

	//create a ROS wrapper for the costmap, passing it a name and a reference to a TransformListener
	//which will configure itself based on parameters
	costmap_2d::Costmap2DROS costmap_local("costmap_local", tf);
	costmap_2d::Costmap2DROS costmap_global("costmap_global", tf);
//	costmap_2d::Costmap2DPublisher(n, 1, "map");

	base_local_planner::TrajectoryPlannerROS tp;
	tp.initialize("my_trajectory_planner", &tf, &costmap_local);
	
	navfn::NavfnROS navfn;
	navfn.initialize("my_navfn_planner", &costmap_global);

	//create a timer for our silly print callback that will call it once a second
//	ros::Timer timer = n.createTimer(ros::Duration(1.0), boost::bind(doSomething, _1, boost::ref(costmap_ros)));

	//start processing data
	ros::spin();

	return(0);

}
