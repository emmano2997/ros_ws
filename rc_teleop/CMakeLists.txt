cmake_minimum_required(VERSION 3.5)
project(rc_teleop)

# Encontrar dependências
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

# Incluir diretórios
include_directories(
  include
)

# Adicionar executável rc_teleop
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

# Adicionar executável rc_teleop_to_rcin
add_executable(rc_teleop_to_rcin src/rc_teleop_to_rcin.cpp)
ament_target_dependencies(rc_teleop_to_rcin
  rclcpp
  sensor_msgs
  geometry_msgs
  tf2_geometry_msgs
  std_msgs
  mavros_msgs
  visualization_msgs
)

add_executable(wheel_controller src/wheel_controller.cpp)
ament_target_dependencies(wheel_controller
  rclcpp
  sensor_msgs
  std_msgs
)

# Instalar os binários
install(TARGETS
  rc_teleop
  rc_teleop_to_rcin
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  rc_teleop
  rc_teleop_to_rcin
  wheel_controller
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
