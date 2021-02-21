#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

using std::placeholders::_1;

int initial_flag = 0;

std::string window_name = "image";

class shutdown_subscriber:public rclcpp::Node
{
    public:
        shutdown_subscriber():Node("shutdown_node")
        {
            sub_ = this->create_subscription<std_msgs::msg::Bool>("btn_msg", 1, std::bind(&shutdown_subscriber::btnmsg_callback, this, _1));
        }
    private:
        
        void btnmsg_callback(const std_msgs::msg::Bool::SharedPtr msg);
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_;
};

void shutdown_subscriber::btnmsg_callback(const std_msgs::msg::Bool::SharedPtr msg)
{
    if(msg->data == 1)
    {
        system("shutdown -P now");
    }
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<shutdown_subscriber>());
    rclcpp::shutdown();
    return 0;
}