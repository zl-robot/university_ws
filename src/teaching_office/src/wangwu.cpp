#include "rclcpp/rclcpp.hpp"
#include "institute_interfaces/srv/course_apply.hpp"

using std::placeholders::_1;
using std::placeholders::_2;


class StaffNode:public rclcpp::Node
{
public:
    StaffNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是教学办公室%s",name.c_str());

        server_ = this->create_service<institute_interfaces::srv::CourseApply>("apply_course",
            std::bind(&StaffNode::apply_course_callback,this,_1,_2));

    }

private:

    void apply_course_callback(const institute_interfaces::srv::CourseApply::Request::SharedPtr request,
        const institute_interfaces::srv::CourseApply::Response::SharedPtr response)
    {
        RCLCPP_INFO(this->get_logger(), "收到来自'%s'学院,'%s'老师的建课申请，课程名称为：'%s'",request->institute.c_str(),request->name.c_str(),request->course.c_str());

        response->success = true;
        response->courseid = 100;


    }

    rclcpp::Service<institute_interfaces::srv::CourseApply>::SharedPtr server_;


    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<StaffNode>("wangwu");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}