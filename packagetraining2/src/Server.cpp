#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class Server_Perkalian : public rclcpp::Node 
{
public:
    Server_Perkalian() : Node("Node_Perkalian")
    {
      server_ = this->create_service<example_interfaces::srv::AddTwoInts>("Ints_Perkalian",
      std::bind(&Server_Perkalian::CallbackPerkalian, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    void CallbackPerkalian(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, 
                           const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        response->sum = request->a * request->b;
        RCLCPP_INFO(this->get_logger(), "request: %d * %d = %d", (int)request->a, (int)request->b, (int)response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Server_Perkalian>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}