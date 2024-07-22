cmake_minimum_required(VERSION 3.8)
project(tracked_objects_crop_box_filter)

# Find dependencies
find_package(ament_cmake_auto REQUIRED)
find_package(rclcpp REQUIRED)
find_package(autoware_auto_perception_msgs REQUIRED)

ament_auto_find_build_dependencies()

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/tracked_objects_crop_box_filter.cpp
)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN "autoware::perception::TrackedObjectsCropBoxFilterNode"
  EXECUTABLE tracked_objects_crop_box_filter_node
)

ament_auto_package(INSTALL_TO_SHARE
  launch
)
