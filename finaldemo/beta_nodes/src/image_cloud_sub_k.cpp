
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <boost/format.hpp>

#include <beta_nodes/steeringMsg.h>
#include <math.h>

// PCL includes
//#include "pcl_ros/point_cloud.h" **needed to comment out this bill kulp for jinx to run
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

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
#include <stdio.h>
#include <string>


#define STEP 10
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
int cycles;


double target_x_sum = 0.0;
double target_y_sum = 0.0;
double target_count = 0.0;
double offsets[47][63];

double targetX;
double targetY;

//callback
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
	ROS_INFO("Callback");
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
	
	cv::erode(range, eroded, cv::Mat());
	cv::imshow("ERODED", eroded);
	
	//ROS_INFO("Eroded image of type %d. ", eroded.type());

	// Convert the image from ROS format to PCL format
	PointCloudXYZRGB cloud;
	//pcl::PointCloud<pcl::PointsXYZ> cloud;
	pcl::fromROSMsg(*cloud_msg, cloud);	

	count = 0;	
	target_count = 0;
	target_x_sum = 0;
	target_y_sum = 0;
	psi_robot=heading;//tf::getYaw(last_map_pose.pose.orientation);//get direction

	coord_ls greenlist; // holds the list of points detected to be orange
	ROS_INFO_STREAM(boost::format("%d ROWS, %d Cols") %eroded.rows %eroded.cols);
	int rows=0, cols=0;
	string my_string;
	
	FILE * file;
	if(cycles<100){
	file = fopen ("myfile.txt" , "w");
	if (file == NULL) ROS_INFO("Error opening file");}
	for (int i = 0; i < eroded.rows-STEP; i+=STEP) 
	{
		rows++;
		for (int j = 0; j < eroded.cols-STEP; j+=STEP) 
		{
			cols++;
			//if (eroded.at<uchar>(i,j) == 255)
			count++;
			// kinect reference frame points
			// Get the corresponding 3D point
			pcl::PointXYZ p = cloud.at(j, i); //j-i or i-j?
			//PointCloudXYZRGB p = cloud.at(j,i);
			if (p.x > 0.1 || p.y > 0.1  || p.z > 0.1) //filter nans
			{
				//ROS_INFO_STREAM(boost::format("Pixel (%d, %d) maps to 3D point (%.2f, %.2f, %.2f) in TF frame = \"%s\"")
				//%i %j %p.x %p.y %p.z %cloud_msg->header.frame_id);
				//ROS_INFO_STREAM(boost::format("Start"));
				// xyz points in kinect frame		
				//double x_k = p.x;
				//double y_k = p.y;
				//double z_k = p.z;
				geometry_msgs::PointStamped map_point;
				geometry_msgs::PointStamped kinect_point;
				tf::Stamped<tf::Point> tf_point;
				//kinect_point.header = cloud_msg->header;
				//kinect_point.header.stamp.sec += 1000000;
				//ROS_INFO("%d.%d",ros::Time::now().sec,ros::Time::now().nsec);
					
				kinect_point.header.frame_id = "/camera_rgb_optical_frame";
				kinect_point.header.stamp = ros::Time(0);
				//Rotate round z axis using p.x
				//kinect_point.point.x = cos(-p.x);
				//kinect_point.point.y = sin(-p.x);
				
				//Rotate round y axis using p.y
				//kinect_point.point.z = -kinect_point.point.x*sin(p.y);
				//kinect_point.point.x = kinect_point.point.x*cos(p.y);
					
				//Apply magnitude of p.z
				//kinect_point.point.x *= p.z;
				//kinect_point.point.y *= p.z;
				//kinect_point.point.z *= p.z;
				
				kinect_point.point.x = p.x;
				kinect_point.point.y = p.y;
				kinect_point.point.z = p.z;
				
				//ROS_INFO("x:%f y:%f z:%f",kinect_point.point.x,kinect_point.point.y,kinect_point.point.z);

				try
				{
					tfl->transformPoint("map", kinect_point, map_point);
					offsets[i/10][j/10] = (offsets[i/10][j/10]*(cycles-1) + map_point.point.z)/cycles;
					if(cycles<100) fprintf(file,"%f,",offsets[i/10][j/10]);
				}
				catch(tf::TransformException& ex)
				{
					ROS_ERROR_STREAM(boost::format("Failed to transform point from \"%s\" to \"map\" frame: %s") %kinect_point.header.frame_id %ex.what());
				}

				double x_m = map_point.point.x;
				double y_m = map_point.point.y;
				double z_m = map_point.point.z;
				
				
				
				if(map_point.point.z>0.07)
				{
					//ROS_INFO("Z: %f",map_point.point.z);
					cv::circle(image, cv::Point(j, i), STEP, CV_RGB(250, 0, 0), 3);
					target_x_sum += x_m;
					target_y_sum += y_m;
					target_count++;
				}
			}
			
		}
		if(cycles<100) fprintf(file,";\n");
		//ROS_INFO("Cols: %d",cols);
		cols=0;
	}
	if(cycles<100) fclose(file);
	//ROS_INFO("Rows: %d",rows);
	rows=0;
	cycles++;
	ROS_INFO("%d",cycles);

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

	//ros::Publisher publishTarget = n.advertise<beta_nodes::targetMsg>("beta_target", 1);
	//beta_nodes::targetMsg m;

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
	pub = nh.advertise<geometry_msgs::PointStamped>("targetPoint", 1);
																																		
	window_name_ = "Image from Kinect";
	cv::namedWindow(window_name_.c_str());
	//while (!tfl->canTransform("map", "camera_link", ros::Time::now())) { ROS_INFO("WAITING FOR camera_link"); ros::spinOnce();}
	ROS_INFO("Done initializing, going into spin mode.");
	ros::Rate naptime(50);
	
			
	geometry_msgs::PointStamped targetPoint;

	while( ros::ok() )
	{
	 	ros::spinOnce();
		
		targetX = target_x_sum/target_count;
		targetY = target_y_sum/target_count;

		ROS_INFO("target x|y : %f | %f",targetX, targetY);

		
		targetPoint.point.x = targetX;
		targetPoint.point.y = targetY;
        pub.publish(targetPoint);

	 	naptime.sleep();
	}
	return 0;
}
