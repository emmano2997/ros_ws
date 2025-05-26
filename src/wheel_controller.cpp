#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"

class WheelController : public rclcpp::Node
{
public:
  WheelController() : Node("wheel_controller")
  {
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10, std::bind(&WheelController::joy_callback, this, std::placeholders::_1));
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/diff_controller/cmd_vel", 10);
    RCLCPP_INFO(this->get_logger(), "Wheel controller node started");
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
  {
    double linear_scale = 0.5;  // Max 0.5 m/s
    double angular_scale = 1.0; // Max 1.0 rad/s
    double linear = msg->axes[1] * linear_scale;  // Left stick vertical
    double angular = msg->axes[3] * angular_scale; // Right stick horizontal

    auto cmd_vel = geometry_msgs::msg::Twist();
    cmd_vel.linear.x = linear;
    cmd_vel.angular.z = angular;
    cmd_vel_pub_->publish(cmd_vel);

    RCLCPP_INFO(this->get_logger(), "Linear: %.2f, Angular: %.2f", linear, angular);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WheelController>());
  rclcpp::shutdown();
  return 0;
}