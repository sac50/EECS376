// Author: Bill Kulp
// Simple program that subscribes to and publishes a point cloud and image
// 3/26/2012

/******************************************************************
PROGRAM DESCRIPTION:
	This node listens to the XBOX Kinect camera feed, both RGB and Depth
	cameras.  It will publish a list of points in map coordinates
	of all orange related pixels.  To do this, it first determines 
	orange points with respect to i j location in the image.  Then it
	applies a transform to convert them to xyz with respect to the 
	kinect.  Then they undergo an additional transform to convert
	to coordinates relative to jinx and then another transform 
	to convert to map coordinates.  At this point they are added 
	to a list and at the conclusion of scanning the whole image, the 
	list is published.

******************************************************************/

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <boost/format.hpp>

#include <beta_nodes/steeringMsg.h>
#include <math.h>
#include "Path.h"
// PCL includes
//#include "pcl_ros/point_cloud.h" **needed to comment out for jinx to run
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

// OpenCV includes
#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <cv_bridge/CvBridge.h>
#include <tf/transform_listener.h>
#include<geometry_msgs/PointStamped.h>

#include <iostream>
#include <fstream>

#define STEP 2 //10
#define PI 3.1415926535897

using std::string;
using sensor_msgs::PointCloud2;


int chart = 0;
// Shorthand for our point cloud type
typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudXYZRGB;

// Global variables here
ros::Publisher pub; 
ros::Publisher             cloud_pub_;
image_transport::Publisher image_pub_;
string window_name_;
Vector position;
double heading;
tf::TransformListener *tfl;
geometry_msgs::PointStamped map_pose;
geometry_msgs::PointStamped temp_pose;


int Hz;
double K;
int clusterOffset, lastClusterOffset;

int loH1, loS1, loV1, hiH1, hiS1, hiV1;
int loH2, loS2, loV2, hiH2, hiS2, hiV2;
int count;


//
void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
	heading = str->heading;
}



// A magical callback that combines an image, cam info, and point cloud
void allCB(const sensor_msgs::ImageConstPtr& image_msg, 
           const sensor_msgs::PointCloud2::ConstPtr& cloud_msg,
           const sensor_msgs::CameraInfo::ConstPtr& cam_msg)
{
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

	cv::cvtColor(image, hsvoutput, CV_BGR2HSV);//put the image in HSV space
	//cv::imshow("HSVOUTPUT", hsvoutput);

	inRange(hsvoutput, cv::Scalar(loH1, loS1, loV1), cv::Scalar(hiH1, hiS1, hiV1), lorange);
	inRange(hsvoutput, cv::Scalar(loH2, loS2, loV2), cv::Scalar(hiH2, hiS2, hiV2), hirange);
	range = lorange+hirange;
	
	cv::erode(range, eroded, cv::Mat()); //cv::Mat() makes this default to a 3x3 erode. Could make it a 5x5 circle I guess?
	cv::imshow("ERODED", eroded);
	
	//ROS_INFO("Eroded image of type %d. ", eroded.type());

	// Convert the image from ROS format to PCL format
	PointCloudXYZRGB cloud;
	pcl::fromROSMsg(*cloud_msg, cloud);	

	count = 0;	

//	for (int i = 2; i < eroded.rows-STEP; i+=STEP) 
//	{
//		for (int j = 2; j < eroded.cols-STEP; j+=STEP) 
//		{
	double theta = (52/180.0) * PI;

	ROS_INFO_STREAM(boost::format("%d ROWS, %d Cols") %eroded.rows %eroded.cols);
	for (int i = 1; i < eroded.rows-1; i+=STEP) {
			for (int j = 1; j < eroded.cols-1; j+=STEP) {
			//	if (eroded.at<uchar>(i,j) == 255)
//						 && eroded.at<uchar>(i-1,j) == 255 && eroded.at<uchar>(i+1,j) == 255 &&
//						 eroded.at<uchar>(i,j-1) == 255 && eroded.at<uchar>(i,j+1) == 255
			//	if (eroded.at<cv::Point3_<uchar>>.x = 255 && eroded.at<cv::Point3_uchar>>.y == 255 && eroded.at<cv::Point3_uchar>>.x
				//if(	eroded.at<cv::Vec3b>(i, j)[0] == 255 && eroded.at<cv::Vec3b>(i,j)[1] == 255 
			//	eroded.at<cv::Vec3b>(i+1, j)[0] == 255 && eroded.at<cv::Vec3b>(i+1, j)[1] == 255 &&	
			//	eroded.at<cv::Vec3b>(i, j-1)[0] == 255 && eroded.at<cv::Vec3b>(i, j-1)[1] == 255 &&	
			//	eroded.at<cv::Vec3b>(i, j+1)[0] == 255 && eroded.at<cv::Vec3b>(i, j+1)[1] == 255 	
	//	if (eroded.at<cv::Vec3b>(i,j)[0] = 255)
			{
								
				count++;
				// kinect reference frame points
				// Get the corresponding 3D point
				pcl::PointXYZRGB p = cloud.at(j, i); //j-i or i-j?
				if (p.x > 0.1 || p.y > 0.1  || p.z > 0.1) 
				{
					//ROS_INFO_STREAM(boost::format("Pixel (%d, %d) maps to 3D point (%.2f, %.2f, %.2f) in TF frame = \"%s\"") %i %j %p.x %p.y %p.z %cloud_msg->header.frame_id);
					// xyz points in kinect frame		
					double x_k = p.x;
					double y_k = p.y;
					double z_k = p.z;
					
					double z_offset = 0.0; //TODO: Really??

					// xyz points in robot frame (base link)
					double x_r = z_k * cos(theta) + y_k * sin(theta);
					double y_r = x_k;
					double z_r = z_k * sin(theta) - y_k * cos(theta) -z_offset;
					//ROS_INFO_STREAM(boost::format("Pixel (%d, %d) maps to 3D point (%.2f, %.2f, %.2f) in Robot frame") %i %j %x_r %y_r %z_r );

					// xyz points in map frame		
					double x_m = position.x + x_r * cos(heading) + y_r * sin(heading);
					double y_m = position.y + x_r * sin(heading) + y_r * cos(heading);
					double z_m = z_r;
			//		ROS_INFO_STREAM(boost::format("OJPixel (%d, %d) KANmaps to 3D point (%.2f, %.2f, %.2f) in Map frame") %i %j %x_m %y_m %z_m );

				//	ROS_INFO_STREAM(boost::format("(%d, %d) to draw circle") %j %i);

					
					temp_pose.point.x = x_k;
					temp_pose.point.y = y_k;
					temp_pose.point.z = z_k;
					temp_pose.header.frame_id = "camera_link";
					
					try {
					  tfl->transformPoint("map", temp_pose, map_pose);
					} catch (tf::TransformException ex) {
					  ROS_ERROR("%s", ex.what());
					}
	//				ROS_INFO_STREAM(boost::format("Pixel (%d, %d) maps to 3D point (%.2f, %.2f, %.2f) in Map frame = \"map?\"") %i %j %map_pose.point.x %map_pose.point.y %map_pose.point.z);
					ROS_INFO_STREAM(boost::format("Z: %d") %map_pose.point.z);

					if (map_pose.point.z < 0.1) {
						cv::circle(image, cv::Point(j, i), STEP, CV_RGB(255, 0, 0), 3);
	//					ROS_INFO_STREAM("STEVE");
					}
					else {
						cv::circle(image, cv::Point(j, i), STEP, CV_RGB(0, 0, 255), 3);
	//					ROS_INFO_STREAM("TESSA");
					}
				}

				// take i j point convert to xyz with respect to kinect
				// this is done pcl::PointXYZRGB command
				// WE ARE HERE
				// take xyz point and apply kan's transform
				// apply transform to put into jinx map frame
			}
		}
			
	}
						
	ROS_INFO("Got %d orange pixels", count);																
	cv::imshow("image", image);
	

	// Show the image.  The window does not update without the cvWaitKey.
	cv::imshow(window_name_.c_str(), cv_ptr->image);
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
	tfl = new tf::TransformListener();

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
							
	// Get some parameters (optional)
	string mystringparam;
	double mydoubleparam;
	private_nh.param("test" , mystringparam, string("this is a default value"));
	private_nh.param("test2", mydoubleparam, 1.0);
	ROS_INFO_STREAM("mystringparam = " << mystringparam);
	ROS_INFO_STREAM("mydoubleparam = " << mydoubleparam);
	
	ros::Subscriber sub1 = nh.subscribe("cmd_corr",1,steeringCallback);													
	// Subscribe to an image, cloud, and camera info.
	// Note the use of image_transport::SubscriberFilter and message_filters::Subscriber.  These allow for synchronization of the topics.
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
	pub = nh.advertise<geometry_msgs::PointStamped>("tapePoint", 1);

	window_name_ = "Image from Kinect";
	cv::namedWindow(window_name_.c_str());
	ROS_INFO("Done initializing, going into spin mode.");
																																				
	while( ros::ok() )
	{
	 	ros::spinOnce();
	}
	return 0;
}
