//=================================================================================================
// Copyright (c) 2012-2016, Institute of Flight Systems and Automatic Control,
// Technische Universität Darmstadt.
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of hector_quadrotor nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "mavros_msgs/msg/rc_in.hpp"
#include "mavros_msgs/msg/override_rc_in.hpp"

class RcTeleopToRCIn : public rclcpp::Node
{
public:
  RcTeleopToRCIn() : Node("rc_teleop_to_rcin")
  {
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10,
      std::bind(&RcTeleopToRCIn::joy_callback, this, std::placeholders::_1)
    );

    rc_override_pub_ = this->create_publisher<mavros_msgs::msg::OverrideRCIn>(
      "mavros/rc/override", 10
    );

    RCLCPP_INFO(this->get_logger(), "rc_teleop_to_rcin node started.");
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr joy_msg)
  {
    auto rc_override = mavros_msgs::msg::OverrideRCIn();
    rc_override.channels[0] = static_cast<uint16_t>((joy_msg->axes[0] + 1.0) * 500 + 1000);  // Roll
    rc_override.channels[1] = static_cast<uint16_t>((joy_msg->axes[1] + 1.0) * 500 + 1000);  // Pitch
    rc_override.channels[2] = static_cast<uint16_t>((joy_msg->axes[3] + 1.0) * 500 + 1000);  // Throttle
    rc_override.channels[3] = static_cast<uint16_t>((joy_msg->axes[2] + 1.0) * 500 + 1000);  // Yaw

    // Define os demais canais como "sem alteração"
    for (int i = 4; i < 8; ++i)
    {
      rc_override.channels[i] = 0;
    }

    rc_override_pub_->publish(rc_override);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<mavros_msgs::msg::OverrideRCIn>::SharedPtr rc_override_pub_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RcTeleopToRCIn>());
  rclcpp::shutdown();
  return 0;
}
