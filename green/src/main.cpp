#include "../include/green/color_filter.hpp"

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<WebcamSubscriber>());
	rclcpp::shutdown();
	return 0;
}
