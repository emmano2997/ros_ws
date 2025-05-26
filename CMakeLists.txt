cmake_minimum_required(VERSION 3.8)
project(laser_rahcm_visualization)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Find ament_cmake first
find_package(ament_cmake REQUIRED)

# Find other ROS 2 packages
find_package(rclcpp REQUIRED)
find_package(urdf REQUIRED)
find_package(xacro REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(robot_state_publisher REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo_ros2_control REQUIRED)
find_package(controller_manager REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(control_msgs REQUIRED)

# Install directories
install(
  DIRECTORY urdf config launch
  DESTINATION share/${PROJECT_NAME}
)

# Add wheel controller executable
add_executable(wheel_controller src/wheel_controller.cpp)
ament_target_dependencies(wheel_controller
  rclcpp
  sensor_msgs
  geometry_msgs
)

# Add teleop executable
add_executable(rc_teleop src/rc_teleop.cpp)
ament_target_dependencies(rc_teleop
  rclcpp
  sensor_msgs
  geometry_msgs
  tf2_geometry_msgs
  std_msgs
  mavros_msgs
  visualization_msgs
)

# Install executables
install(TARGETS
  wheel_controller
  rc_teleop
  DESTINATION lib/${PROJECT_NAME}
)

# Export dependencies
ament_export_dependencies(
  rclcpp
  sensor_msgs
  geometry_msgs
  tf2_geometry_msgs
  std_msgs
  mavros_msgs
  visualization_msgs
  robot_state_publisher
  rviz_common
  rviz_default_plugins
  gazebo_ros
  gazebo_ros2_control
  controller_manager
  hardware_interface
  control_msgs
)

ament_package()