#include "rclcpp/rclcpp.hpp"


class StudentNode:public rclcpp::Node
{
public:
    StudentNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是学生%s",name.c_str());

    }

private:

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<StudentNode>("lisi");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}