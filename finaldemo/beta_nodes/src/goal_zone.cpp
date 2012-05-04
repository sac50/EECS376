
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <boost/format.hpp>

#include <beta_nodes/steeringMsg.h>
#include <beta_nodes/orangeGoal.h>
#include <math.h>

// PCL includes
//#include "pcl_ros/point_cloud.h" **needed to comment out this bill kulp for jinx to run
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include<geometry_msgs/PointStamped.h>

// OpenCV includes
#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <cv_bridge/CvBridge.h>
#include "Path.h"
#include <iostream>
#include <fstream>

// Phidgets
#include <phidgets/interface_kit_params.h>
#include <phidgets/interface_kit.h>
#include <stdio.h>

#define STEP 1 
#define PI 3.1415926

using std::string;
using sensor_msgs::PointCloud2;

int chart = 0;
// Shorthand for our point cloud type
typedef pcl::PointCloud<pcl::PointXYZ> PointCloudXYZRGB;

//typedef std::pair<float, float> coord;
typedef std::vector<geometry_msgs::PointStamped> coord_ls;

// Global variables here
ros::Publisher pub;
ros::Publisher             cloud_pub_;
image_transport::Publisher image_pub_;
string window_name_;
Vector position;
double heading;
double psi_robot;
tf::TransformListener *tfl;
nav_msgs::Odometry last_odom;
geometry_msgs::PoseStamped last_map_pose;

int Hz;
double K;
int clusterOffset, lastClusterOffset;

int loH1, loS1, loV1, hiH1, hiS1, hiV1;
int loH2, loS2, loV2, hiH2, hiS2, hiV2;
int count;

bool goalFound = false;

ros::ServiceClient client_interface_kit;

//callback
void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
	heading = str->heading;
}


// Phidget Callback
void interfaceKitCallback(const phidgets::interface_kit_params::ConstPtr& ptr) {
	phidgets::interface_kit_params ifk = *ptr;
	switch (ifk.value_type) {
		case 1: {
			ROS_INFO("DIGITAL INPUT %d State %d", ifk.index, ifk.value);
			break;
		} 
		case 2: {
			ROS_INFO("DIGITAL INPUT %d State %d", ifk.index, ifk.value);
			break;
		} 
		case 3: {
			ROS_INFO("DIGITAL INPUT %d State %d", ifk.index, ifk.value);
			break; 
		}

	}
}

void set_digital_output( int output_index, int state) {
	phidgets::interface_kit srv;
	srv.request.index = output_index;
	srv.request.value_type = 1;
	srv.request.value = state;
	srv.response.ack = 0;
	if (client_interface_kit.call(srv)) {
		if ((int)srv.response.ack == 1) {
			ROS_INFO("CHANGED DIGITAL OUTPUT %d TO STATE %d", output_index, state);
		}
		else {
			ROS_INFO("RETURNED %d", (int) srv.response.ack);
		}
	} else {
		ROS_ERROR("FAILED TO CALL SERVICE INTERFACE_KIT");
	}
}

// A magical callback that combines an image, cam info, and point cloud
void allCB(const sensor_msgs::ImageConstPtr& image_msg, 
           const sensor_msgs::PointCloud2::ConstPtr& cloud_msg,
	const sensor_msgs::CameraInfo::ConstPtr& cam_msg)
{
	ROS_INFO("Callback");
	ROS_INFO_STREAM("HEADER.FRAME_ID: " << cloud_msg->header.frame_id);
	// Convert the image from ROS format to OpenCV format
	
	cv_bridge::CvImagePtr cv_ptr;
	try	{
		cv_ptr = cv_bridge::toCvCopy(image_msg);
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
		return;
	}
	//ROS_INFO_STREAM(boost::format("Callback got an image in format %s, size %dx%    d")
           //% cv_ptr->encoding % cv_ptr->image.rows % cv_ptr->image.cols );

	sensor_msgs::CvBridge bridge;
	cv::Mat image;
	cv::Mat hsvoutput;
	cv::Mat hirange;
	cv::Mat lorange;
	cv::Mat range;
	cv::Mat eroded;
	cv::Mat out;
	cv::Mat temp;


	image = cv::Mat(bridge.imgMsgToCv(image_msg, "bgr8"));//store the image data from the message in "image"	

	//cv::cvtColor(image, hsvoutput, CV_BGR2HSV);//put the image in HSV space
	//cv::imshow("HSVOUTPUT", hsvoutput);
	 
	//inRange(hsvoutput, cv::Scalar(loH1, loS1, loV1), cv::Scalar(hiH1, hiS1, hiV1), lorange);
	//inRange(hsvoutput, cv::Scalar(loH2, loS2, loV2), cv::Scalar(hiH2, hiS2, hiV2), hirange);
	//range = lorange+hirange;
	 
	//cv::erode(range, eroded, cv::Mat()); //cv::Mat() makes this default to a 3x3 erode. Could make it a 5x5 circle I guess?
	//cv::imshow("ERODED", eroded);


	double xpoint = 0.0;
	double ypoint = 0.0;
	int pointCounter = 0;
	// Convert the image from ROS format to PCL format
	PointCloudXYZRGB cloud;
	//pcl::PointCloud<pcl::PointsXYZ> cloud;
	pcl::fromROSMsg(*cloud_msg, cloud);	
	psi_robot=heading;//tf::getYaw(last_map_pose.pose.orientation);//get direction
	//ROS_INFO_STREAM(boost::format("STARTING THRU %d ROWS, %d Cols") %eroded.rows %eroded.cols);
	geometry_msgs::PointStamped point;
	for (int i = 100; i < image.rows-1; i+=STEP) {//rows
		//for (int j = 1; j < eroded.cols-1; j+=STEP) {//cols
		for (int j = 213; j < 426; j++) {	
			pcl::PointXYZ p = cloud.at(j, i); //j-i or i-j?
			bool flag = false;
			//if (p.x != p.x && p.y != p.y && p.z != p.z) {
			if (p.x > 0.01 || p.y > 0.01  || p.z > 0.01) {
				geometry_msgs::PointStamped map_point;
				geometry_msgs::PointStamped kinect_point;
				tf::Stamped<tf::Point> tf_point;
				kinect_point.header.frame_id = "/camera_rgb_optical_frame";
				kinect_point.header.stamp = ros::Time(0);
				kinect_point.point.x = p.x;
				kinect_point.point.y = p.y;
				kinect_point.point.z = p.z;
				try {
					tfl->transformPoint("map", kinect_point, map_point);
				}
				catch(tf::TransformException& ex) {
					ROS_ERROR_STREAM(boost::format("Failed to transform point from \"%s\" to \"map\" frame: %s") %kinect_point.header.frame_id %ex.what());
				}
				if (map_point.point.z > 0.03) {
					cv::circle(image, cv::Point(j, i), 20, CV_RGB(250, 0, 0), 3);
					point.header = kinect_point.header;				
					xpoint += map_point.point.x;
					ypoint += map_point.point.y;
					pointCounter++;
				}
				else {
					cv::circle(image, cv::Point(j, i), 5, CV_RGB(0,0,250),3);
				}
			}
		}//cols		
	}//row

	cv::imshow("image_from_obstacle", image);

	double distanceFromGoalZone = 0.0;
	double wayX = -1.33;
	double wayY = 22.54;

	bool orange_goal_found = false;
	if (pointCounter > 0) { orange_goal_found = true;}
	
	distanceFromGoalZone = sqrt(pow((position.x - wayX),2) + pow((position.y - wayY),2));
	double goalX = xpoint/pointCounter;
	double goalY = ypoint/pointCounter;
	ROS_INFO("-------------------------------------------------------------------------------");
	ROS_INFO("DISTANCE FROM GOAL ZONE : %f", distanceFromGoalZone);
	ROS_INFO("ORANGE GOAL FOUND: %d", orange_goal_found);
	ROS_INFO("POINT COUNTER: %d", pointCounter);
	if (distanceFromGoalZone < 0.5 && orange_goal_found) {
	//	if (goalX < 0) { goalX += 0.205; }
	//	else { goalX -= 0.205; }
		//ROS_INFO("PUBLISHED POINT (%f, %f)", goalX, goalY);	
		
		
		point.point.x = goalX;
		point.point.y = goalY;
		point.point.z = 0.0;
	
		//if (goalFound) {
			beta_nodes::orangeGoal orangeGoalMsg;
			orangeGoalMsg.point = point;
			pub.publish(orangeGoalMsg);

			ROS_INFO("PUBLISHED POINT (%f, %f)", goalX, goalY);	
		//	goalFound = true;
		//}
	}
	else {
		ROS_INFO("NO GOAL OBJECT VISIBLE OR NOT IN GOAL ZONE");
	}
	// Show the image.  The window does not update without the cvWaitKey.
//	cv::imshow(window_name_.c_str(), cv_ptr->image);
	cvWaitKey(5);											
	// Publish the modified image
 	image_pub_.publish(cv_ptr->toImageMsg());
}



int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "rate_limiter");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh("~");
	tf::TransformListener hey;
	tfl = &hey;

	 private_nh.param("loH1", loH1, 0);
	 private_nh.param("loS1", loS1, 0);
	 private_nh.param("loV1", loV1, 0);
	 private_nh.param("hiH1", hiH1, 0);
	 private_nh.param("hiS1", hiS1, 0);
	 private_nh.param("hiV1", hiV1, 0);
	  
	 private_nh.param("loH2", loH2, 0);
	 private_nh.param("loS2", loS2, 0);
	 private_nh.param("loV2", loV2, 0);
	 private_nh.param("hiH2", hiH2, 0);
	 private_nh.param("hiS2", hiS2, 0);
	 private_nh.param("hiV2", hiV2, 0);
	 
	 private_nh.param("K", K, 0.0);
	 private_nh.param("Hz", Hz, 1);

	image_transport::ImageTransport it(nh);

	ros::Subscriber interface_kit_sub = nh.subscribe("phidgets/interface_kit", 1, interfaceKitCallback);
    client_interface_kit = nh.serviceClient<phidgets::interface_kit>("interface_kit");
							
	// Get some parameters (optional)
	string mystringparam;
	double mydoubleparam;
	private_nh.param("test" , mystringparam, string("this is a default value"));
	private_nh.param("test2", mydoubleparam, 1.0);
	ROS_INFO_STREAM("mystringparam = " << mystringparam);
	ROS_INFO_STREAM("mydoubleparam = " << mydoubleparam);
														
	// Subscribe to an image, cloud, and camera info.
	// Note the use of image_transport::SubscriberFilter and message_filters::Subscriber.  These allow for synchronization of the topics.
	ros::Subscriber sub = nh.subscribe("cmd_corr",1,steeringCallback);
	image_transport::SubscriberFilter image_sub   (it, "in_image", 3);
	message_filters::Subscriber<sensor_msgs::PointCloud2> cloud_sub(nh, "in_cloud", 3);
	message_filters::Subscriber<sensor_msgs::CameraInfo> cam_info_sub(nh, "in_cam_info", 3);
																				
	// This sync policy will invoke a callback if it receives one of each message with matching timestamps
	typedef message_filters::sync_policies::ApproximateTime
		   <sensor_msgs::Image, sensor_msgs::PointCloud2, sensor_msgs::CameraInfo> MySyncPolicy;
																								   	
	// Synchronize the three topics.  MySyncPolicy(10) tells it to maintain a buffer of 10 messages.
	message_filters::Synchronizer<MySyncPolicy>
	sync(MySyncPolicy(10), image_sub, cloud_sub, cam_info_sub);
																												   	
	// Hook the callback into the sync policy
	sync.registerCallback( boost::bind(&allCB, _1, _2, _3) );
																																
	// publishers for the image and point cloud
	image_pub_ = it.advertise(ros::this_node::getName() + "/out_image", 1);
	cloud_pub_ = nh.advertise<sensor_msgs::PointCloud2>(ros::this_node::getName() + "/out_cloud", 1);
	
	// publisher for the point we found
	//pub = nh.advertise<geometry_msgs::PointStamped>("orangeGoal", 1);
	pub = nh.advertise<beta_nodes::orangeGoal>("orangeGoal",1);																																	
	window_name_ = "Image from Kinect";
	cv::namedWindow(window_name_.c_str());
	//while (!tfl->canTransform("map", "camera_link", ros::Time::now())) { ROS_INFO("WAITING FOR camera_link"); ros::spinOnce();}
	ROS_INFO("Done initializing, going into spin mode.");
	ros::Rate naptime(50);
	
	
	set_digital_output(6,1);

																																				
	while( ros::ok() )
	{
	 	ros::spinOnce();
	 	naptime.sleep();
	}
	return 0;
}
