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
#include "sensor_msgs/msg/joint_state.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"  
#include "geometry_msgs/msg/pose_stamped.hpp"   
#include "std_msgs/msg/float64.hpp"             
#include "std_msgs/msg/float32.hpp"             
#include "std_msgs/msg/int32.hpp"                
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"  
#include <string>                                

class RcTeleopNode : public rclcpp::Node
{
public:
  RcTeleopNode() : Node("rc_teleop")
  {
    // Declarar e obter parâmetro para nome do tópico de entrada
    this->declare_parameter<std::string>("joy_topic", "joy_raw");
    std::string joy_topic = this->get_parameter("joy_topic").as_string();

    // Assinatura no tópico do joystick
    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      joy_topic, 10,
      std::bind(&RcTeleopNode::joy_callback, this, std::placeholders::_1)
    );

    // Publicador do tópico de saída
    joy_pub_ = this->create_publisher<sensor_msgs::msg::Joy>("joy", 10);

    RCLCPP_INFO(this->get_logger(), "rc_teleop node started. Subscribing to '%s'", joy_topic.c_str());
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
  {
    joy_pub_->publish(*msg);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr joy_pub_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RcTeleopNode>());
  rclcpp::shutdown();
  return 0;
}