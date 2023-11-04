import launch
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument as DLA
from launch.substitutions import LaunchConfiguration as LC

def generate_launch_description():
    banana = Node(
        package='banana',
        executable='webcam_driver_pub',
        name='webcam_driver'
    )
    green = Node(
        package='green',
        executable='color_filter',
        name='color_filter',
        output='screen',
        parameters=[
            {
                "param_hi": [255, 255, 255],
                "param_lo": [200, 200, 200],
                "desired_co": [255, 0, 0]
            }
            ]
        )
    return launch.LaunchDescription([
        banana,
        green,
    ])
