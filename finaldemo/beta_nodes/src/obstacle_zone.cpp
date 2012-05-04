
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

#include <beta_nodes/freeSpace.h>
#include <beta_nodes/PathSegment.h>

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

int thresholdLevel = 240;

std::vector<beta_nodes::PathSegment> waypoints;
int waypointCounter = 0;
double orangeX = 0.0;
double orangeY = 0.0;

//callback
void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
	heading = str->heading;
}


bool orange_goal_found = false; // covers when goal found to goal picked up
bool orange_goal_picked_up = false; // so we dont find a goal after we picked it up
bool orange_goal_detected = false; // prevents us from publishing different goal points, ensures we only publish one
void orangeGoalCallback(const beta_nodes::orangeGoal::ConstPtr& og) {
	
	ROS_INFO("WAYPOINT COUNTER %d", waypointCounter);
	ROS_INFO("ORANGE GOAL DETECTED %d", orange_goal_detected);
	if (waypointCounter == 3 && !orange_goal_detected) {
		orange_goal_found = true;
		orange_goal_detected = true;
		orangeX = og->point.point.x;
		orangeY = og->point.point.y;
		ROS_INFO("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		ROS_INFO("ORANGE POINT FOUND");
	}
}


// A magical callback that combines an image, cam info, and point cloud
void allCB(const sensor_msgs::ImageConstPtr& image_msg, 
           const sensor_msgs::PointCloud2::ConstPtr& cloud_msg,
	const sensor_msgs::CameraInfo::ConstPtr& cam_msg)
{
	//ROS_INFO("Callback");
	//ROS_INFO_STREAM("HEADER.FRAME_ID: " << cloud_msg->header.frame_id);
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
	//cv::imshow("ERODED", eroded);
	
	//ROS_INFO("Eroded image of type %d. ", eroded.type());

	// Convert the image from ROS format to PCL format
	PointCloudXYZRGB cloud;
	//pcl::PointCloud<pcl::PointsXYZ> cloud;
	pcl::fromROSMsg(*cloud_msg, cloud);	

	count = 0;	

	psi_robot=heading;//tf::getYaw(last_map_pose.pose.orientation);//get direction

	coord_ls greenlist; // holds the list of points detected to be orange
	//ROS_INFO_STREAM(boost::format("STARTING THRU %d ROWS, %d Cols") %eroded.rows %eroded.cols);
	
	int zone [image.cols];
	geometry_msgs::PointStamped point;
	// Start at 0 column and go up by row until row 240
	for (int i = 0; i < image.cols; i+=STEP) {
		for (int j = 479; j > 239; j-=STEP) {
	//	for (int j = 479; j > 210; j-=STEP) {
			pcl::PointXYZ p = cloud.at(i,j);
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
				ROS_ERROR_STREAM(boost::format("Failed to transform point"));
			}
			if (map_point.point.z > 0.03) {
				//red points indicate the location of objects above the ground plane
				cv::circle(image, cv::Point(i, j), 3, CV_RGB(250, 0, 0), 3); 
				point.header = kinect_point.header;
				// Obstacle Found
				zone [i] = 479-j;
				// Go to next column
				break;							
			}
			else {
				//cv::circle(image, cv::Point(i,j), STEP, CV_RGB(0,250,0),3); //green
			}
			zone[i] = thresholdLevel;
		}
	}

	// Find the start i and end i for largest continuious 
	int startI = 0;
	int endI = 0;
	bool startCount = false;	
	int maxStartI = 0;
	int maxEndI = 0;
	
	for (int i = 0; i < image.cols; i ++) {
		// Start Count
		if (zone[i] == thresholdLevel && !startCount) {
			if ( (endI - startI) > (maxEndI - maxStartI) ) {
				maxStartI = startI;
				maxEndI = endI;
			}
			startI = i;
			endI = i;
			startCount = true;
		} else if (zone[i] == thresholdLevel && startCount) {
			endI = i;
	//		ROS_INFO("START: %d | END: %d", startI, endI);
		} else {	
			startCount = false;
		}
	}
	
	//ROS_INFO ("FINISHED");
	//ROS_INFO("END I : %d", endI);
	//ROS_INFO("START I: %d", startI);
	//ROS_INFO("MAX END I: %d", maxEndI);
	//ROS_INFO("MAX START I: %d", maxStartI);

	if ( (endI - startI) > (maxEndI - maxStartI) ) {
		maxStartI = startI;
		maxEndI = endI;
	}
	
	bool obstacleFound = false;
	// No obstacle found
//	if (maxStartI == 0 && maxEndI == (image.cols - 1) ) {
//		obstacleFound = true;
//	}
//
//	ROS_INFO("LARGEST FREE SPACE BETWEEN %d and %d", maxStartI, maxEndI);
	// Find the midpoint
	int midpoint = (maxEndI + maxStartI) / 2;
	pcl::PointXYZ p = cloud.at(midpoint, thresholdLevel);

	// draw go to point on map with a big blue circle
	cv::circle(image, cv::Point(midpoint,thresholdLevel), 35, CV_RGB(0,0,255),3);
	// Compute transfom of the point to map
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
		ROS_ERROR_STREAM(boost::format("Failed to transform point"));
	}
	point.header = kinect_point.header;
	point.point.x = map_point.point.x;
	point.point.y = map_point.point.y;
	point.point.z = 0.0;

    	// Fudge Factor for no obstacles in view
    	if (maxStartI < 100 && maxEndI > 610 || waypointCounter == 3 || waypointCounter == 4) {
		 // Go to way point
		beta_nodes::PathSegment wpoint;
		wpoint = waypoints.back();
		point.point.x = wpoint.ref_point.x;
		point.point.y = wpoint.ref_point.y;

		// ROS_INFO("===================================================================");
		// ROS_INFO("GOING TO WAY POINT");
	    	// ROS_INFO("====================================================================");
	}  
	else {
		//ROS_INFO("===================================================================");
		//ROS_INFO("GOING TO OBSTACLE POINT");
	    //	ROS_INFO("====================================================================");
	}
	if (orange_goal_found && !orange_goal_picked_up) {
		point.point.x = orangeX;
		point.point.y = orangeY;
		//ROS_INFO("===================================================================");
		//ROS_INFO("GOING TO ORANGE POINT");
	     //	ROS_INFO("====================================================================");
	}

	beta_nodes::freeSpace freeSpaceMsg;
	freeSpaceMsg.point = point;
	freeSpaceMsg.obstacleFound = obstacleFound;
	
//	if (!orange_goal_found) {
		pub.publish(freeSpaceMsg);
	
	//	ROS_INFO("Published Point (%f, %f)", point.point.x, point.point.y);
	//	ROS_INFO("Obstacle Found: %d", obstacleFound);
	//	ROS_INFO("-------------------------------------------------------------------------------------------------------------------");
//	}
/*
	point.point.x = red_avg_x;
	point.point.y = red_avg_y;
	point.point.z = 0.0;
	ROS_INFO_STREAM(boost::format("Published Point (%lf, %lf") %red_avg_x %red_avg_y);
	pub.publish(point);
*/
	cv::imshow("image", image);

	// Show the image.  The window does not update without the cvWaitKey.
	//cv::imshow(window_name_.c_str(), cv_ptr->image);
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

	/*
		Set the way points vector
		using vector and pop back so add points in reverse order
	*/

	beta_nodes::PathSegment pathSeg6;
	pathSeg6.ref_point.x = 8.47;
	pathSeg6.ref_point.y = 14.99;
	waypoints.push_back(pathSeg6);

	beta_nodes::PathSegment pathSeg5;
	pathSeg5.ref_point.x = 5.53;
	pathSeg5.ref_point.y = 11.92;
	waypoints.push_back(pathSeg5);

	beta_nodes::PathSegment pathSeg4;
	pathSeg4.ref_point.x = -3.52;
	pathSeg4.ref_point.y = 20.77;
	waypoints.push_back(pathSeg4);

	beta_nodes::PathSegment pathSeg3;
	pathSeg3.ref_point.x = 0.72;
	pathSeg3.ref_point.y = 24.59;
	waypoints.push_back(pathSeg3);
	
	beta_nodes::PathSegment pathSeg2;
	pathSeg2.ref_point.x = -2.23;
	pathSeg2.ref_point.y = 21.69;
	waypoints.push_back(pathSeg2);

	beta_nodes::PathSegment pathSeg1;
	pathSeg1.ref_point.x = -3.52;
	pathSeg1.ref_point.y = 20.77;
	waypoints.push_back(pathSeg1);

	beta_nodes::PathSegment pathSeg;
	pathSeg.ref_point.x = 5.53;
	pathSeg.ref_point.y = 11.92;
	waypoints.push_back(pathSeg);


/**** Temp run */
/*
	beta_nodes::PathSegment pathSeg3;
	pathSeg3.ref_point.x = 15.19;
	pathSeg3.ref_point.y = 6.82;
	waypoints.push_back(pathSeg3);

	beta_nodes::PathSegment pathSeg2;
	pathSeg2.ref_point.x = 7.27;
	pathSeg2.ref_point.y = 13.94;
	waypoints.push_back(pathSeg2);

	beta_nodes::PathSegment pathSeg4;
	pathSeg4.ref_point.x = 6.82;
	pathSeg4.ref_point.y = 13.24;
	waypoints.push_back(pathSeg4);

	beta_nodes::PathSegment pathSeg5;
	pathSeg5.ref_point.x = 4.87;
	pathSeg5.ref_point.y = 12.39;
	waypoints.push_back(pathSeg5);


*/
	
/**** END TEMP RUN */
							
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
	ros::Subscriber sub1 = nh.subscribe("orangeGoal",1,orangeGoalCallback);
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
	pub = nh.advertise<beta_nodes::freeSpace>("tapePoint", 1);
																																		
	window_name_ = "Image from Kinect";
	cv::namedWindow(window_name_.c_str());
	//while (!tfl->canTransform("map", "camera_link", ros::Time::now())) { ROS_INFO("WAITING FOR camera_link"); ros::spinOnce();}
	ROS_INFO("Done initializing, going into spin mode.");
	ros::Rate naptime(50);
	
																																				
	while( ros::ok() )
	{
	 	ros::spinOnce();
		// check to see if we are within .25 meters of waypoint
		// if so pop and move to next way point
		double distanceFromWayPoint = 0.0;
		beta_nodes::PathSegment wpoint;
		wpoint = waypoints.back();
		double wayX = wpoint.ref_point.x;
		double wayY = wpoint.ref_point.y;
		
		distanceFromWayPoint = sqrt(pow((position.x - wayX),2) + pow((position.y - wayY),2));
		if (!orange_goal_found) {
			if (distanceFromWayPoint < .5) {
				waypoints.pop_back();
				ROS_INFO("==============================================================================");
				ROS_INFO("REMOVING A WAY POINT");
				waypointCounter++;
			}
		} else {
			distanceFromWayPoint = sqrt(pow((position.x - orangeX),2) + pow((position.y - orangeY),2));
			if (distanceFromWayPoint < 0.05) {
				ROS_INFO("==============================================================================");
				ROS_INFO("REMOVING THE ORANGE WAY POINT");
				orange_goal_found = false;
				orange_goal_picked_up = true;
			}
		}
	 	naptime.sleep();
	}
	return 0;
}
