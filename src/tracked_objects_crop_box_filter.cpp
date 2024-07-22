// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "tracked_objects_crop_box_filter.hpp"

namespace autoware
{
namespace perception
{

TrackedObjectsCropBoxFilterNode::TrackedObjectsCropBoxFilterNode(const rclcpp::NodeOptions & options)
: Node("crop_box_filter_node", options)
{
  // Subscriber
  sub_objects_ = create_subscription<autoware_auto_perception_msgs::msg::TrackedObjects>(
    "input/objects", rclcpp::QoS{1},
    std::bind(&TrackedObjectsCropBoxFilterNode::trackedObjectsCallback, this, std::placeholders::_1));

  // Publishers
  pub_inside_objects_ = create_publisher<autoware_auto_perception_msgs::msg::TrackedObjects>(
    "output/inside_objects", rclcpp::QoS{1});
  pub_outside_objects_ = create_publisher<autoware_auto_perception_msgs::msg::TrackedObjects>(
    "output/outside_objects", rclcpp::QoS{1});

  // Parameters
  filter_unknown_ = declare_parameter<bool>("filter_unknown", false);
  min_x_ = declare_parameter<double>("min_x", -300.0);
  max_x_ = declare_parameter<double>("max_x", 300.0);
  min_y_ = declare_parameter<double>("min_y", -300.0);
  max_y_ = declare_parameter<double>("max_y", 300.0);
  min_z_ = declare_parameter<double>("min_z", -300.0);
  max_z_ = declare_parameter<double>("max_z", 300.0);
}

void TrackedObjectsCropBoxFilterNode::trackedObjectsCallback(const autoware_auto_perception_msgs::msg::TrackedObjects::SharedPtr msg)
{
  auto inside_objects = std::make_shared<autoware_auto_perception_msgs::msg::TrackedObjects>();
  auto outside_objects = std::make_shared<autoware_auto_perception_msgs::msg::TrackedObjects>();

  inside_objects->header = msg->header;
  outside_objects->header = msg->header;

  for (const auto & object : msg->objects) {
    const auto & pose = object.kinematics.pose_with_covariance.pose;

    if (filter_unknown_ && !object.classification.empty() && 
        object.classification.back().label == autoware_auto_perception_msgs::msg::ObjectClassification::UNKNOWN) {
      continue; // Completely ignore unknown objects
    }

    if (pose.position.x >= min_x_ && pose.position.x <= max_x_ &&
        pose.position.y >= min_y_ && pose.position.y <= max_y_ &&
        pose.position.z >= min_z_ && pose.position.z <= max_z_) {
      inside_objects->objects.push_back(object);
    } else {
      outside_objects->objects.push_back(object);
    }
  }
  pub_inside_objects_->publish(*inside_objects);
  pub_outside_objects_->publish(*outside_objects);
}

}  // namespace perception
}  // namespace autoware

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(autoware::perception::TrackedObjectsCropBoxFilterNode)
