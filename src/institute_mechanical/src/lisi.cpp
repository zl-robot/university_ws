#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"

using std::placeholders::_1;

class StudentNode:public rclcpp::Node
{
public:
    StudentNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是学生%s",name.c_str());

        sub_hw = this->create_subscription<std_msgs::msg::String>("homework",10,std::bind(&StudentNode::topic_callback,this,_1));
        pub_No = this->create_publisher<std_msgs::msg::UInt32>("studentID",10);
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_hw;
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_No;

    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),"收到：'%s'",msg->data.c_str());

        std_msgs::msg::UInt32 studengid;
        studengid.data = 10;
        pub_No->publish(studengid);
        RCLCPP_INFO(this->get_logger(),"学号：%d,收到：'%s'",studengid.data,msg->data.c_str());

    };

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<StudentNode>("lisi");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}