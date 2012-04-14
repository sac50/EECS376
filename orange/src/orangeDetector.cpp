#include <ros/ros.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <geometry_msgs/Twist.h>

#include <cv_bridge/CvBridge.h>

#include <eecs376_vision_demo1/lib_demo.h>

#include <eecs376_vision_demo1/cvblob.h>

using namespace cv;

void allCB(const sensor_msgs::ImageConstPtr& image_msg,
		   const sensor_msgs::PointCloud2::ConstPtr& cloud_msg,
		   const sensor_msgs::CameraInfo::ConstPtr& cam_msg) {
	// Convert the image from ros format to opencv
	cv_bridge::CvImagePtr cv_ptr;
	try {
		cv_ptr = cv_bridge::toCvCopy(image_msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR_STREAM("CV_BRIDGE_EXCEPTION: " << e.what());
		return;
	}
	
	imshow("Callback Camera", cv_ptr->image);
	cvWaitKey(5);	

}

void normalizeColors(const Mat& src, Mat& out) {
	Mat temp;
	src.convertTo(temp, CV_32F);
	vector<Mat> mats;
	split(temp, mats);
	Mat total = mats[0] + mats[1] + mats[2];

	mats[0] = mats[0] / total;
	mats[1] = mats[1] / total;
	mats[2] = mats[2] / total;
	merge(mats, temp);
	temp.convertTo(out, CV_8U, 255);
}

int main (int argc, char **argv) {
    ros::init(argc, argv, "orangeDetector");
	ROS_INFO("HELLO BETAS");
	ros::NodeHandle nh;
	imgage_transport::ImageTransport it(nh);

	import_transport::SubscribeFilter image_sub (it, "in_image",3);
	message_filters::Subscriber<sensor_msgs::PointCloud2> cloud_sub(nh, "in_cloud",3);
	message_filters::Subscriber<sensor_msgs::CameraInfo> cam_info_sub(nh, "in_cam_info", 3);
	typedef message_filters::sync_policies::ApproximateTime
		   <sensor_msgs::Image, sensor_msgs::PointCloud2, sensor_msgs::CameraInfo> MySyncPolicy;

		   message_filters::Synchronizer<MySyncPolicy>
		   	   sync(MySyncPolicy(10), image_sub, cloud_sub, cam_info_sub);
			   	
					// Hook the callback into the sync policy
						sync.registerCallback( boost::bind(&allCB, _1, _2, _3) );

	while (ros::ok()) {
		ros::spinOnce();
	}




	// Open File
/*
	IplImage *img = cvLoadImage("orange_strap.jpg");
	if (!img) {
		printf("Error: Couldn't open image file");
	}

	// Display The Image
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image", img);

	IplImage* out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
*/
/*	
	cvSmooth(img, out, CV_BLUR, 7, 7);
	cvNamedWindow("CV_BLUR", CV_WINDOW_AUTOSIZE);
	cvShowImage("CV_BLUR", out);

	cvSmooth(img, out, CV_GAUSSIAN, 7, 7);
	cvNamedWindow("CV_GAUSSIAN", CV_WINDOW_AUTOSIZE);
	cvShowImage("CV_GAUSSIAN", out);

	cvSmooth(img, out, CV_MEDIAN, 7, 7);
	cvNamedWindow("CV_MEDIAN", CV_WINDOW_AUTOSIZE);
	cvShowImage("CV_MEDIAN", out);
*/
/*
	cvErode(img, out, NULL, 1);
	cvNamedWindow("CV_ERODE", CV_WINDOW_AUTOSIZE);
	cvShowImage("CV_ERODE", out);

	cvDilate(img, out, NULL, 1);
	cvNamedWindow("CV_DILATE", CV_WINDOW_AUTOSIZE);
	cvShowImage("CV_DILATE", out);
*/
/*
	CvPoint seedPoint = cvPoint(288, 400);
        CvScalar color = CV_RGB(250, 0,0);
        cvFloodFill(out, seedPoint, color, cvScalarAll(5.0), cvScalarAll(5.0), NULL, 4, NULL);
        cvNamedWindow("CV_FLOODFILL", CV_WINDOW_AUTOSIZE);
        cvShowImage("CV_FLOODFILL", out);
*/
	
	// Wait for user to press a key in the GUI window
//	cvWaitKey(0);
/*
	IplImage* out = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U, 3);
	cvSmooth(img, out, CV_GAUSSIAN, 11, 11);
	cvNamedWindow("Normal", CV_WINDOW_AUTOSIZE);
	cvShowImage("Normal", out);

	IplImage* flood = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	CvPoint seedPoint = cvPoint(305, 195);
	CvScalar color = CV_RGB(250, 0,0);
	cvFloodFill(flood, seedPoint, color, cvScalarAll(5.0), cvScalarAll(5.0), NULL, 4, NULL);
	cvNamedWindow("FloodFill", CV_WINDOW_AUTOSIZE);
	cvShowImage("FloodFill", flood);	
*/
	// color R 246 G 141 B 146
	
/*
	cvThreshold(img, out,240 ,255, CV_THRESH_BINARY);	
	cvNamedWindow("Threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold", out);
	cvWaitKey(0);	

	cvErode(img, out, NULL, 1);
        cvNamedWindow("CV_ERODE", CV_WINDOW_AUTOSIZE);
        cvShowImage("CV_ERODE", out);

      	cvThreshold(img, out,240 ,255, CV_THRESH_BINARY);
        cvNamedWindow("Threshold1", CV_WINDOW_AUTOSIZE);
        cvShowImage("Threshold1", out);
*/
/*
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, imgHSV, CV_BGR2HSV);
	IplImage* imgThreshold = cvCreateImage(cvGetSize(img), 8, 1);
	cvInRangeS(imgHSV, cvScalar(150,100,100), cvScalar(255, 255, 255), imgThreshold);
	
	cvNamedWindow("Threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage("Threshold", imgThreshold);
	cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
	cvShowImage("HSV", imgHSV);

	cvWaitKey(0);
	
	// Free the resources
	cvDestroyWindow("Image");
	cvReleaseImage(&img);
	cvDestroyWindow("out");
	cvReleaseImage(&out);
*/
	return 0;

}

