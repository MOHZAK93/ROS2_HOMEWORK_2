#ifndef COLOR_FILTER_HPP_
#define COLOR_FILTER_HPP_

#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "rcl_interfaces/msg/parameter_event.hpp"

class WebcamSubscriber : public rclcpp::Node
{
	public:
		WebcamSubscriber();

	private:
		void CallbackImageProcessor(const sensor_msgs::msg::Image::SharedPtr msg);
	
	sensor_msgs::msg::Image::SharedPtr msg_;
	rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
	rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr parameter_event_sub;
	rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};
#endif
