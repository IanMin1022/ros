#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "ManualControl.h"

class Camera_node {
public:
  Camera_node(void);
  ~Camera_node(void);
  void subscribe(ros::NodeHandle&);
  void Reading_camera_1(const geometry_msgs::PoseStamped&);
  void Reading_camera_2(const geometry_msgs::PoseStamped&);
  void Reading_camera_3(const geometry_msgs::PoseStamped&);
  void Reading_camera_4(const geometry_msgs::PoseStamped&);
  void Reading_camera_5(const geometry_msgs::PoseStamped&);
  void Reading_camera_6(const geometry_msgs::PoseStamped&);
  void Reading_camera_7(const geometry_msgs::PoseStamped&);

private:
  ros::Subscriber sub[7];
};

extern Camera_node* camera_node;

#endif
