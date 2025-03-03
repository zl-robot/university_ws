#include "rclcpp/rclcpp.hpp"


class StaffNode:public rclcpp::Node
{
public:
    StaffNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是教学办公室%s",name.c_str());

    }

private:

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<StaffNode>("wangwu");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}