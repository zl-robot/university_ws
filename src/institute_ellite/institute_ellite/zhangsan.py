import rclpy
from rclpy.node import Node

from institute_interfaces.srv import SubmitScore

from institute_interfaces.srv import CourseApply

class TeacherNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("我是%s,是一名老师！" %name)

        self.server_ = self.create_service(SubmitScore,"submitandscore",self.submitscore_callback)

        self.client_ = self.create_client(CourseApply,"apply_course")

    def recv_studentID_callback(self,studengID):
        self.get_logger().info('学号：%d已经收到了作业' % studengID.data)

    def submitscore_callback(self,request,response):
        self.get_logger().info("收到来自: %s (学号： %d)的课程 %s 的第 %d 次作业" % (request.name, request.studentid, request.content, request.no))

        response.success = True
        response.score = 100
        return response
    
    def apply_course(self):
        self.get_logger().info("申请建课")
        while not self.client_.wait_for_service(1.0):
            self.get_logger().info("教学办公室没人")
        
        requestcourse = CourseApply.Request()
        requestcourse.institute = "Ellite Institute of Engineering"
        requestcourse.name = self.get_name()
        requestcourse.course = "The Application of Mobile Robots"
        self.client_.call_async(requestcourse).add_done_callback(self.courseapply_response_callback)
    
    
    def courseapply_response_callback(self,response):
        result = response.result()
        if result.success == True:
            self.get_logger().info("申请建课成功，课程编号为：%d" % result.courseid)
        else:
            self.get_logger().info("很遗憾，申请建课不成功")


def main(args=None):
    rclpy.init(args=args)
    node = TeacherNode("zhangsan")
    node.apply_course()
    rclpy.spin(node)
    rclpy.shutdown()