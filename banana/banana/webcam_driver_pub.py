#!/usr/bin/env python3

"""Webcam Image Publisher Node"""

import rclpy
from rclpy.node import Node
import cv2 as cv
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from time import time


class ImagePublisher(Node):
    """"A node that published webcam images to a subscriber"""

    def __init__(self):
        """Initialize node"""
        super().__init__('webcam_publisher')
        
        # Create publisher
        self.publisher_ = self.create_publisher(Image, '/webcam/image_raw', 10)

        # Create timer
        self.timer = self.create_timer(0.1, self.publish_image)

        # Initializw CvBridge to convert between OpenCV images and ROS2 images 
        self.bridge = CvBridge()

        # Activate webcam
        self.cap = cv.VideoCapture(0)
        
    def publish_image(self):
        """Node publisher method"""

        unix_time = str(time())
        if self.cap.isOpened():
            ret, frame = self.cap.read()

            if ret == True:
                # Put timestamp on image
                font = cv.FONT_HERSHEY_SIMPLEX
                font_scale = 1
                font_color = (0, 0, 255)
                font_thickness = 2
                position = (30, 50)
                cv.putText(frame, unix_time, position, font, font_scale, font_color, font_thickness)
            
                # Convert the Numpy image to ROS2 image
                ros2_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')

                # Publish image
                self.publisher_.publish(ros2_image)
            self.get_logger().info("Image published")

def main(args=None):
    """Entry point"""

    rclpy.init(args=args)

    node = ImagePublisher()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.capture.release()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
