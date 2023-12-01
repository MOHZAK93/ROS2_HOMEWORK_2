#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "iostream"

class ColorFilter : public rclcpp::Node {
public:
    ColorFilter() : Node("color_filter") {
        // Subscribe to the raw image topic from the webcam
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/webcam/image_raw", 10,
            [this](const sensor_msgs::msg::Image::SharedPtr msg) {
                // Convert ROS2 image message to OpenCV image
                cv_bridge::CvImagePtr cv_ptr;
                try {
                    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
                } catch (cv_bridge::Exception& e) {
                    // Handle conversion errors
                    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
                    return;
                }

                // Color filtering based on parameters
                cv::Mat filtered_image = filterImage(cv_ptr->image);

                // Publish the filtered image to a new topic
                sensor_msgs::msg::Image::SharedPtr filtered_msg = cv_bridge::CvImage(msg->header, "bgr8", filtered_image).toImageMsg();
                image_publisher_->publish(*filtered_msg);
            });

        // Create a publisher for the filtered image
        image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/webcam/filtered_image", 10);
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;

    // Function to filter the input image based on color parameters
		cv::Mat filterImage(cv::Mat input_image) {

        // Define the color range in BGR
        //cv::Scalar lowerRed = cv::Scalar(10, 10, 100);
        //cv::Scalar upperRed = cv::Scalar(100, 100, 255);
		std::vector<long> default_hi = {255, 255, 255};
		std::vector<long> default_lo = {200, 200, 200};
		std::vector<long> default_co = {0, 0, 255};

        // Apply color filter to highlight red regions
        //cv::inRange(input_image, lowerRed, upperRed, output_image);
        //output_image.setTo(cv::Scalar(10, 10, 255), output_image);
		//Change color of white objects to red in image
		for (int i = 0; i < input_image.rows; i++) {
			for (int j =0; j < input_image.cols; j++) {
				cv::Vec3b& pixel = input_image.at<cv::Vec3b>(i, j);
				if (pixel[0] > default_lo[0] && pixel[1] > default_lo[1] && pixel[2] > default_lo[2]){
					pixel[0] = default_co[0];
					pixel[1] = default_co[1];
					pixel[2] = default_co[2];

				}
			}
		}

        return input_image;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "Hi from strawberry_package";

    // Initialize the ROS2 node
    rclcpp::init(argc, argv);
    // Spin the node
    rclcpp::spin(std::make_shared<ColorFilter>());
    // Shutdown ROS2
    rclcpp::shutdown();
    return 0;
}
