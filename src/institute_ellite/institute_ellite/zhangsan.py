import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from std_msgs.msg import UInt32

class TeacherNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("我是%s,是一名老师！" %name)

        self.pub_hw = self.create_publisher(String,"homework",10)
        self.i = 1
        self.timer_period = 2
        self.timer = self.create_timer(self.timer_period,self.timer_callback)

        self.substudentID = self.create_subscription(UInt32,"studentID",self.recv_studentID_callback,10)

    def timer_callback(self):
        msg = String()
        msg.data = '第%d次作业已发布,请查收。' % (self.i)
        self.pub_hw.publish(msg)
        self.get_logger().info('同学们，我发布了作业："%s"' % msg.data)
        self.i += 1

    def recv_studentID_callback(self,studengID):
        self.get_logger().info('学号：%d已经收到了作业' % studengID.data)


def main(args=None):
    rclpy.init(args=args)
    node = TeacherNode("zhangsan")
    rclpy.spin(node)
    rclpy.shutdown()