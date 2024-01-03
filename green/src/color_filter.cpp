#include "../include/green/color_filter.hpp"
using std::placeholders::_1;

/**
 * WebcamSubscriber - ROS2 image subscriber class
 *
 */

WebcamSubscriber::WebcamSubscriber()
	: rclcpp::Node("Webcam_Subscriber")
{
	//Declare parameters for colors
	this->declare_parameter<std::vector<long>>("param_hi", {255, 255, 255});
	this->declare_parameter<std::vector<long>>("param_lo", {200, 200, 200});
	this->declare_parameter<std::vector<long>>("desired_co", {0, 0, 255});

	// Create Subscriber
	subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
			"/webcam/image_raw", 10,std::bind(&WebcamSubscriber::CallbackImageProcessor, this, _1));
}

void WebcamSubscriber::CallbackImageProcessor(const sensor_msgs::msg::Image::SharedPtr msg)
{
	//Create CvBridge
	cv_bridge::CvImagePtr cv_ptr;

	//Convert message to openCV formate
	cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

	cv::Mat cv_image = cv_ptr->image;

	//Get parameter values
	std::vector<long>my_param_hi = this->get_parameter("param_hi").as_integer_array();
	std::vector<long>my_param_lo = this->get_parameter("param_lo").as_integer_array();
	std::vector<long>my_param_de = this->get_parameter("desired_co").as_integer_array();

	//Set parameters back to default value when they are changed externally
	std::vector<long> default_hi = {255, 255, 255};
	std::vector<long> default_lo = {200, 200, 200};
	//std::vector<long> default_co = {0, 0, 255};
	this->set_parameters({rclcpp::Parameter("param_hi", default_hi)});
	this->set_parameters({rclcpp::Parameter("param_lo", default_lo)});
	//this->set_parameters({rclcpp::Parameter("desired_co", default_co)});

	//Change color of white objects to red in image
	for (int i = 0; i < cv_image.rows; i++) {
		for (int j =0; j < cv_image.cols; j++) {
			cv::Vec3b& pixel = cv_image.at<cv::Vec3b>(i, j);
			if (pixel[0] > my_param_lo[0] && pixel[1] > my_param_lo[1] && pixel[2] > my_param_lo[2]){
				pixel[0] = my_param_de[0];
				pixel[1] = my_param_de[1];
				pixel[2] = my_param_de[2];
			}
		}
	}

	//Convert image back to ros2 message
	msg_ = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", cv_image).toImageMsg();

	RCLCPP_INFO(this->get_logger(), "I heard");

	publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/webcam/image_raw_2", 10);
	publisher_->publish(*msg_);
}
