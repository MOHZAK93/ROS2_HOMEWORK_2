#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
using std::placeholders::_1;

/**
 * WebcamSubscriber - ROS2 image subscriber class
 *
 */

class WebcamSubscriber : public rclcpp::Node
{
  public:
    WebcamSubscriber()
    : Node("Webcam_Subscriber")
    {
		// Create Subscriber
		subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
				"/webcam/image_raw", 10, std::bind(&WebcamSubscriber::image_processor, this, _1));
    }

  private:
    void image_processor(const sensor_msgs::msg::Image::SharedPtr msg)
    {
		//Create CvBridge
		cv_bridge::CvImagePtr cv_ptr;
		
		//Convert message to openCV formate
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

		cv::Mat cv_image = cv_ptr->image;
		
		//Change color of white objects to red in image
		for (int i = 0; i < cv_image.rows; i++) {
			for (int j =0; j < cv_image.cols; j++) {
				cv::Vec3b& pixel = cv_image.at<cv::Vec3b>(i, j);
				if (pixel[0] > 220 && pixel[1] > 220 && pixel[2] > 220){
					pixel[0] = 0;
					pixel[1] = 0;
					pixel[2] = 255;
				}
			}
		}
		
		//Convert image back to ros2 message
		msg_ = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_image).toImageMsg();

		RCLCPP_INFO(this->get_logger(), "I heard");

		publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/webcam/image_raw_2", 10);
		publisher_->publish(*msg_);
    }
	sensor_msgs::msg::Image::SharedPtr msg_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WebcamSubscriber>());
  rclcpp::shutdown();
  return 0;
}
