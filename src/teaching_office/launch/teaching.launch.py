# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

# 定义函数名称为：generate_launch_description
def generate_launch_description():
    zhangsan_node = Node(
        package="institute_ellite",
        executable="zhangsan_node"
        )
    wangwu_node = Node(
        package="teaching_office",
        executable="wangwu_node"
        )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription([zhangsan_node, wangwu_node])
    # 返回让ROS2根据launch描述执行节点
    return launch_description