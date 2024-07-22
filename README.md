# Tracked Objects Crop Box Filter
Tested in Ubuntu 22.04 / Humble

## Purpose

Filter TrackedObjects by area, optionally removing Unknown objects.

### tracked_objects_crop_box_filter

Splits a tracked objects topic into `inside` objects and `outside` objects

### Core Parameters

| Name    | Type   | Default Value | Description                               |
| ------- | ------ | ------------- | ----------------------------------------- |
| `~/input/objects`  | `TrackedObjects` | - | `input object` launch file arg |
| `~/output/inside_objects`  | `TrackedObjects` | - | `inside_output_topic` launch file arg |
| `~/output/outside_objects`  | `TrackedObjects` | - | `outside_output_topic` |
| `filter_unknown` | bool | false | completely filter UNKNOWN class objects |
| `min_x` | double | -300.0          | x-coordinate minimum value for crop range |
| `max_x` | double | 300.0           | x-coordinate maximum value for crop range |
| `min_y` | double | -300.0          | y-coordinate minimum value for crop range |
| `max_y` | double | 300.0           | y-coordinate maximum value for crop range |
| `min_z` | double | -300.0          | z-coordinate minimum value for crop range |
| `max_z` | double | 300.0           | z-coordinate maximum value for crop range |

### Usage
```
ros2 launch crop_box_filter tracked_object_crop_box_filter.launch.xml input_topic:=/input/tracked_objects inside_output_topic:=/output/inside outside_output_topic:=/output/outside 
```
