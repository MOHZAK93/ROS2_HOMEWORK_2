#!/usr/bin/env python3

from .webcam_driver_pub import ImagePublisher
import rclpy

rclpy.init()

node = ImagePublisher()
    
try:
    rclpy.spin(node)
except KeyboardInterrupt:
    node.capture.release()
    rclpy.shutdown()

