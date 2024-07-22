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

#ifndef TRACKED_OBJECTS_CROP_BOX_FILTER_HPP_
#define TRACKED_OBJECTS_CROP_BOX_FILTER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <autoware_auto_perception_msgs/msg/tracked_objects.hpp>

namespace autoware
{
namespace perception
{

class TrackedObjectsCropBoxFilterNode : public rclcpp::Node
{
public:
  explicit TrackedObjectsCropBoxFilterNode(const rclcpp::NodeOptions & options);

private:
  void trackedObjectsCallback(const autoware_auto_perception_msgs::msg::TrackedObjects::SharedPtr msg);

  rclcpp::Subscription<autoware_auto_perception_msgs::msg::TrackedObjects>::SharedPtr sub_objects_;
  rclcpp::Publisher<autoware_auto_perception_msgs::msg::TrackedObjects>::SharedPtr pub_inside_objects_;
  rclcpp::Publisher<autoware_auto_perception_msgs::msg::TrackedObjects>::SharedPtr pub_outside_objects_;

  bool filter_unknown_;
  double min_x_;
  double max_x_;
  double min_y_;
  double max_y_;
  double min_z_;
  double max_z_;
};

}  // namespace perception
}  // namespace autoware

#endif  // TRACKED_OBJECTS_CROP_BOX_FILTER_HPP_
