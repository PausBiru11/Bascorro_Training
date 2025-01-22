#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "example_interfaces/srv/set_bool.hpp"

class NumberSubscriber: public rclcpp::Node 
{

public:
    NumberSubscriber() : Node("Node_Number_Counter"), data_(0)
    {
        subscriber_ = this->create_subscription<std_msgs::msg::Int32>("Number", 10,
        std::bind(&NumberSubscriber::callbackNumberNews, this, std::placeholders::_1));

        publisher_=this->create_publisher<std_msgs::msg::Int32>("Number_Count", 10);

        server_ = this->create_service<example_interfaces::srv::SetBool>("Reset_Counter",
        std::bind(&NumberSubscriber::CallbackResetNumber, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "Subscriber Menerima Pesan :)");
    }

private:
    void callbackNumberNews(const std_msgs::msg::Int32::SharedPtr msg)
    {
        data_ += msg->data;
        auto new_msg = std_msgs::msg::Int32();
        new_msg.data = data_;  
        publisher_->publish(new_msg);
    }
    
    void CallbackResetNumber(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                             const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if (request->data) {

            data_= 0;
            response->success = true;
            response->message = "Counter Diulang Kembali T_T";

        } else {

            response->success = false;
            response->message = "Counter Tidak Diulang.";

        }
    }

    int data_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberSubscriber>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}