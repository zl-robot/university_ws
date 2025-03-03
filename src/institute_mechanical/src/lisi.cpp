#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "institute_interfaces/msg/homework.hpp"

using std::placeholders::_1;

class StudentNode:public rclcpp::Node
{
public:
    StudentNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是学生%s",name.c_str());

        sub_hw = this->create_subscription<institute_interfaces::msg::Homework>("homework",10,std::bind(&StudentNode::topic_callback,this,_1));
        
        pub_No = this->create_publisher<std_msgs::msg::UInt32>("studentID",10);
    }

private:
    
    rclcpp::Subscription<institute_interfaces::msg::Homework>::SharedPtr sub_hw;
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_No;

    void topic_callback(const institute_interfaces::msg::Homework::SharedPtr msg)
    {
        
        RCLCPP_INFO(this->get_logger(),"收到课程：'%s'的第%d次作业",msg->content.c_str(),msg->no);

        std_msgs::msg::UInt32 studengid;
        studengid.data = 10;
        pub_No->publish(studengid);
        RCLCPP_INFO(this->get_logger(),"学号：%d,收到课程：'%s'的第%d次作业",studengid.data, msg->content.c_str(), msg->no);

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