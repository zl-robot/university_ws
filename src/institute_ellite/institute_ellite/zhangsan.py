import rclpy
from rclpy.node import Node

class TeacherNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("我是%s,是一名老师！" %name)


def main(args=None):
    rclpy.init(args=args)
    node = TeacherNode("zhangsan")
    rclpy.spin(node)
    rclpy.shutdown()