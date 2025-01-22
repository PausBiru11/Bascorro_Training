#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class NumberPublisher: public rclcpp::Node 
{
    
public:
    NumberPublisher(): Node("Node_Number_Publisher"), number_(2)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("Number", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&NumberPublisher::publishNews, this));

        RCLCPP_INFO(this->get_logger(), "Angka Diluncurkan.");
    }

private:
    void publishNews()
    {
       auto msg = std_msgs::msg::Int32();
       msg.data = number_;
       publisher_->publish(msg); 
    }

    int number_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}