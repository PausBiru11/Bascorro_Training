#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class Server_Client : public rclcpp::Node 
{
public:
    Server_Client() : Node("Node_Client")
    {
     threads_.push_back(std::thread(std::bind(&Server_Client::clientPerkalian, this, 9, 3)));
     threads_.push_back(std::thread(std::bind(&Server_Client::clientPerkalian, this, 15, 3)));
     threads_.push_back(std::thread(std::bind(&Server_Client::clientPerkalian, this, 9, 7)));
     threads_.push_back(std::thread(std::bind(&Server_Client::clientPerkalian, this, 56, 3)));
    }

private:
    void clientPerkalian(int a, int b)
    {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("Ints_Perkalian");
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Menunggu Server Launching....");
        }

         auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
         request->a = a;
         request->b = b;

         auto future = client->async_send_request(request);

         try 
         {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "%d * %d = %d", a, b, (int)response->sum);
         }
         catch(const std::exception &e)
         {
            RCLCPP_ERROR(this->get_logger(), "Gagal Menerima Response Dari Server....");
         }

    }
    std::vector<std::thread> threads_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Server_Client>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}