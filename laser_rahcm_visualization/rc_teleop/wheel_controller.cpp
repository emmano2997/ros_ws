#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

class WheelController : public rclcpp::Node
{
public:
  WheelController() : Node("wheel_controller")
  {
    // Subscriber for joy messages
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10,
      std::bind(&WheelController::joy_callback, this, std::placeholders::_1)
    );

    // Publisher for wheel velocities
    wheel_vel_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
      "/velocity_controllers/commands", 10
    );

    RCLCPP_INFO(this->get_logger(), "Wheel controller node started");
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
  {
    // Simple control: left stick vertical for forward/back, right stick horizontal for rotation
    double linear = msg->axes[1];  // Typically left stick vertical
    double angular = msg->axes[3]; // Typically right stick horizontal

    // Calculate wheel velocities (simple differential drive)
    double left = linear - angular;
    double right = linear + angular;

    // Publish wheel velocities
    auto wheel_vel = std_msgs::msg::Float64MultiArray();
    wheel_vel.data = {left, right};
    wheel_vel_pub_->publish(wheel_vel);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr wheel_vel_pub_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WheelController>());
  rclcpp::shutdown();
  return 0;
}