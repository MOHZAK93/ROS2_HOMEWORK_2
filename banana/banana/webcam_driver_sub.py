#!/usr/bin/env python3
"""Webcam Image Subscriber Node"""

import rclpy
from rclpy.node import Node
import cv2 as cv
from sensor_msgs.msg import Image

class ImageSubscriber(Node):
    """Creates a node to subscribe to messages from a webcam publisher"""

    def __init__(self):
        super().__init__('webcam_subscriber') 
        self.subscriber_ = self.create_subscription(Image, '/webcam/image_raw', self.subscriber_image, 10)
        self.subscriber_
        
    def subscriber_image(self, ros2_image):
        self.get_logger().info("Image Received")

def main(args=None):
    rclpy.init(args=args)

    node = ImageSubscriber()
    
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
