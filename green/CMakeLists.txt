cmake_minimum_required(VERSION 3.8)
project(green)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(color_filter src/color_filter.cpp)
ament_target_dependencies(color_filter
	"rclcpp"
	"sensor_msgs"
	"cv_bridge"
)

#Install launch files
install(DIRECTORY
	launch
	DESTINATION	share/${PROJECT_NAME}/
)
install(TARGETS
	color_filter
	DESTINATION lib/${PROJECT_NAME})

ament_package()