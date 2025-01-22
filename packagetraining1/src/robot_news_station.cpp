#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNode: public rclcpp::Node 
{
public:
    RobotNode() : Node("robot_node"), robot_name_("BASCORRO")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&RobotNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "Bascorro Launched.");
    }

private:
    void publishNews()
    {
       auto msg = example_interfaces::msg::String();
       msg.data = std::string("Hi, This Is ") + robot_name_ + std::string (" From EWS");
       publisher_->publish(msg);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}