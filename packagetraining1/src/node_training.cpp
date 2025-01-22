#include "rclcpp/rclcpp.hpp"

class Node1 : public rclcpp::Node 
{
public:
    Node1() : Node("cpp_testnode"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Gusy");

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&Node1::timerCallback, this));
    }

private:
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Node1>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}