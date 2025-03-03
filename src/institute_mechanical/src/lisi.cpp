#include "rclcpp/rclcpp.hpp"

#include "institute_interfaces/srv/submit_score.hpp"

using std::placeholders::_1;


class StudentNode:public rclcpp::Node
{
public:
    StudentNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"我是学生%s",name.c_str());

        client_ = this->create_client<institute_interfaces::srv::SubmitScore>("submitandscore");

    }

    void submit_hw()
    {
        RCLCPP_INFO(this->get_logger(),"提交作业");
        while(!client_->wait_for_service(std::chrono::seconds(1)))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(),"等待服务器第过程中被打断");
                return;
            }
            RCLCPP_INFO(this->get_logger(),"等待服务器上线中");
        }

        auto request = std::make_shared<institute_interfaces::srv::SubmitScore_Request>();


        request->name = "lisi";
        request->studentid = 10;
        request->content = "The Application of mobile robots";

        this->get_parameter("homework_no",homework_no);
        // unsigned int novelsNum = int(request->money/novel_price); //应给小说数量


        request->no = homework_no;

        RCLCPP_INFO(this->get_logger(),"提交：课程：'%s'的第%d次作业", request->content.c_str(),request->no);

        client_->async_send_request(request,std::bind(&StudentNode::submit_callback,this,_1));

    }

    void submit_callback(rclcpp::Client<institute_interfaces::srv::SubmitScore>::SharedFuture response)
    {
        auto result = response.get();

        RCLCPP_INFO(this->get_logger(),"得到的成绩为：%d", result->score);
    }

private:

    unsigned int homework_no = 1;
    
    rclcpp::Client<institute_interfaces::srv::SubmitScore>::SharedPtr client_;

    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<StudentNode>("lisi");
    node->submit_hw();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}