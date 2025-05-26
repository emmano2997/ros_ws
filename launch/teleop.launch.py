from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_share = get_package_share_directory('laser_rahcm_visualization')
    urdf_file = os.path.join(pkg_share, 'urdf', 'rahcm.urdf.xacro')
    control_config = os.path.join(pkg_share, 'config', 'diff_drive_controller.yaml')

    # Processar Xacro para URDF
    robot_description = {'robot_description': Command(['xacro ', urdf_file])}

    return LaunchDescription([
        # Iniciar Gazebo
        ExecuteProcess(
            cmd=['gazebo', '--verbose', '-s', 'libgazebo_ros_factory.so'],
            output='screen'
        ),
        # Robot state publisher
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            output='screen',
            parameters=[robot_description]
        ),
        # Controller manager
        Node(
            package='controller_manager',
            executable='ros2_control_node',
            parameters=[robot_description, control_config],
            output='screen'
        ),
        # Spawn controller
        Node(
            package='controller_manager',
            executable='spawner',
            arguments=['diff_controller'],
            output='screen'
        ),
        # Joy node
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            output='screen'
        ),
        # Wheel controller
        Node(
            package='laser_rahcm_visualization',
            executable='wheel_controller',
            name='wheel_controller',
            output='screen'
        )
    ])