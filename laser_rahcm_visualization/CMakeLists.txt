cmake_minimum_required(VERSION 3.8)
project(laser_rahcm_visualization)

# Encontra todos os pacotes necessários
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(urdf REQUIRED)
find_package(xacro REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)  # Added
find_package(tf2_geometry_msgs REQUIRED)  # Added
find_package(std_msgs REQUIRED)
find_package(mavros_msgs REQUIRED)  # Added
find_package(visualization_msgs REQUIRED)  # Added
find_package(robot_state_publisher REQUIRED)
find_package(rviz2 REQUIRED)
find_package(gazebo_ros REQUIRED)
#find_package(gazebo_ros2_control REQUIRED)
#find_package(controller_manager REQUIRED)
#find_package(hardware_interface REQUIRED)
#find_package(control_msgs REQUIRED)

# Instalação do arquivo URDF
install(
  DIRECTORY urdf
  DESTINATION share/${PROJECT_NAME}
)

# Instalação dos arquivos de lançamento
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# Adicione o executável do controlador de rodas
add_executable(wheel_controller 
  src/wheel_controller.cpp
)
ament_target_dependencies(wheel_controller
  rclcpp
  sensor_msgs
  std_msgs
)

# Executável do teleop (corrected path and dependencies)
add_executable(rc_teleop 
  src/rc_teleop.cpp
)
ament_target_dependencies(rc_teleop
  rclcpp
  sensor_msgs
  std_msgs
)

# Instale todos os executáveis
install(TARGETS
  wheel_controller
  rc_teleop
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()