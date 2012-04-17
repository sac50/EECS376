#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <pcl/io/pcd_io.h>
#include <string>

class PointCloudToImage
{
		public:
			void clould_cb (const sensor_msgs::PointCloud2ConstPtr& cloud) {
				if ((cloud->width * cloud->height) == 0) {
					return;  // cloud is not dense
				}
				try {
					pcl::toROSMsg (*cloud, image_); // convert the cloud
				}
				catch (std::runtime_error e) {
					ROS_ERROR_STREAM("Error in converting cloud to image message: " << e.what());
				}
				image_pub_.publish(image_);
			}

			PointCloudToImage () : cloud_topic_("input"), image_topic_("output") {
				sub_ = nh_.subscribe (cloud_topic_, 30, &PointCloudToImage::cloud_cb, this);
				image_pub_ = nh_.advertise<sensor_msgs::Image> (image_topic_, 30);

				// print info about the node
				std::string r_ct = nh_.resolveName (cloud_topic_);
				std::string r_it = nh_.resolveName (image_topic_);

				ROS_INFO_STREAM("Listening for incoming data on topic " << r_ct);
				ROS_INFO_STREAM("Publishing image on topic " << r_it);
	
			}
			private:
				ros::NodeHandle nh_;
				sensor_msgs::Image image_;
				std::string cloud_topic_;
				std::string image_topic_;
				ros::Subscriber sub_;
				ros::Publisher image_pub;
			};

			int main (int argc, char **argv) {
				ros::init(argc, argv, "convert_pointcloud_to_image");
				PointCloudToImage pci;
				ros::spin();
				return 0;
			}
