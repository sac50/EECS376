//Simple kinect image stream subscriber. Reads the kinect raw RGB image, publishes points where orangey stuff is.
#include <ros/ros.h>
#include <boost/format.hpp>

// OpenCV includes
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <cv_bridge/CvBridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#include<geometry_msgs/Twist.h> //data type for velocities

//using std::string, cv ;
using namespace cv;
using std::string;
// Global variables here
image_transport::Publisher image_pub_;
string window_name_;

int Hz; //set by params
double K; // constant to multiply offset by to achieve a turning angle
int clusterOffset, lastClusterOffset;

int loH1, loS1, loV1, hiH1, hiS1, hiV1;
int loH2, loS2, loV2, hiH2, hiS2, hiV2;

// A callback for an image
void imageCB(const sensor_msgs::ImageConstPtr& image_msg)
{
	// Convert the image from ROS format to OpenCV format
	// cv_ptr is a CvImagePtr which has a cv::Mat as a class member.
	// See http://www.ros.org/doc/api/cv_bridge_redesign/html/namespacecv__bridge.html
	cv_bridge::CvImagePtr cv_ptr;
	try	{
		cv_ptr = cv_bridge::toCvCopy(image_msg);
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
		return;
	}
	
	ROS_INFO_STREAM(boost::format("Callback got an image in format %s, size %dx%d")
		% cv_ptr->encoding % cv_ptr->image.rows % cv_ptr->image.cols );

	// Draw something on the image
//	if( cv_ptr->image.rows > 100 && cv_ptr->image.cols > 100 )
//	{
//		cv::circle(cv_ptr->image, cv::Point(50, 50), 40, CV_RGB(255,0,0));
//	}

	// Display the image.  The window does not update without the cvWaitKey.
	cv::imshow(window_name_.c_str(), cv_ptr->image);
	
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

	inRange(hsvoutput, Scalar(loH1, loS1, loV1), Scalar(hiH1, hiS1, hiV1), lorange);
	inRange(hsvoutput, Scalar(loH2, loS2, loV2), Scalar(hiH2, hiS2, hiV2), hirange);
	range = lorange+hirange;
	//cv::imshow("RANGE", range);

	cv::erode(range, eroded, Mat());
	//cv::imshow("ERODED", eroded);

	double x = 0.0;
	double y = 0.0;
	double counter = 0.0;
	for (int i = 0; i < eroded.rows; i++) {
		for (int j = 0; j < eroded.cols; j++) {
			if (eroded.at<cv::Vec3b>(i,j)[0] == 255 && eroded.at<cv::Vec3b>(i,j)[1] == 255) {
				//ROS_INFO("(%d,%d)", i, j);
				//std::cout << "(" << i << "," << j << + ")" << std::endl;
				x+=i;
				y+=j;
				counter+=1;
			}
		}
	}
	double xF = x / (counter+1);
	double yF = y / (counter+1); //some kludgy divide by zero protection
	int xFinal = int (xF);
	int yFinal = int (yF);
	clusterOffset = (yFinal -( eroded.cols/2));
	if (abs(clusterOffset) > 200) clusterOffset = 0; //boundary condition
	ROS_INFO("CENTER: (%d, %d)", xFinal, yFinal);
	ROS_INFO("FRAME (%d x %d): Offset %d", eroded.rows, eroded.cols, clusterOffset);
			
	cvWaitKey(5);
	
	// Publish the updated image
  image_pub_.publish(cv_ptr->toImageMsg()); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "simple_image_sub");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
	geometry_msgs::Twist cmd_vel;

	// Get some parameters
	ros::NodeHandle private_nh("~");
/*	string mystringparam;
	double mydoubleparam;
	private_nh.param("test" , mystringparam, string("this is a default value"));
	private_nh.param("test2", mydoubleparam, 1.0 );
	ROS_INFO_STREAM("mystringparam = " << mystringparam);
	ROS_INFO_STREAM("mydoubleparam = " << mydoubleparam);
*/
	
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
	
	clusterOffset = 0;
	lastClusterOffset = clusterOffset;
	ros::Rate naptime(Hz); 
	
	// Subscribe to an image. Note the use of image_transport::Subscriber instead of ros::Subscriber
	image_transport::Subscriber image_sub = it.subscribe("in_image", 1, boost::bind(&imageCB, _1) );
	
	// publisher for the output image, again using image_transport
    image_pub_ = it.advertise(ros::this_node::getName() + "/out_image", 1);

	cmd_vel.angular.z = 0;
	cmd_vel.linear.x = 0; 

	window_name_ = "Image from Kinect";
	cv::namedWindow(window_name_.c_str());
	ROS_INFO("Done initializing, going into spin mode.");

	while( ros::ok() )
	{
		ros::spinOnce();
		if (lastClusterOffset != clusterOffset)
		{
			cmd_vel.angular.z = K*((lastClusterOffset+clusterOffset)/2);
			ROS_INFO("Z: %f",  cmd_vel.angular.z);

			lastClusterOffset = clusterOffset;

			pub.publish(cmd_vel);
		}
		naptime.sleep(); 
  	}
  
	return 0;
}
