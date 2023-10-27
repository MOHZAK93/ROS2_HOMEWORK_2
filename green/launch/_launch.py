import launch
from launch_ros.actions import Node

def generate_launch_description():
    return launch.LaunchDescription([
        Node(
            package='banana',
            executable='webcam_driver_pub',
            name='webcam_driver'),
        Node(
            package='green',
            executable='color_filter',
            name='color_filter'),
])
