#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/set_bool.hpp"

class ResetCounter: public rclcpp::Node 
{
    
public:
    ResetCounter(): Node("Reset_Counter")
    {
        client_ = this->create_client<example_interfaces::srv::SetBool>("Reset_Counter");

        while (!client_ ->wait_for_service(std::chrono::seconds(1)))
        {
           RCLCPP_INFO(this->get_logger(), "Menunggu Server Aktif....");
        }

        send_reset_request(true);
    }

    void send_reset_request(bool reset)
    {
        auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
        request->data = reset;

        auto result = client_->async_send_request(request);
    }

private:
    rclcpp::Client<example_interfaces::srv::SetBool>::SharedPtr client_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ResetCounter>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}