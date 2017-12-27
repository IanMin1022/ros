#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>

class Script_subscriber {
public:
  Script_subscriber(void);
  ~Script_subscriber(void);
  void subscribe(ros::NodeHandle&);
  void Script_node_1(const std_msgs::String::ConstPtr&);
  void Script_node_2(const std_msgs::String::ConstPtr&);
  void Script_node_3(const std_msgs::String::ConstPtr&);
  void Script_node_4(const std_msgs::String::ConstPtr&);
  void Script_node_5(const std_msgs::String::ConstPtr&);
  void Script_node_6(const std_msgs::String::ConstPtr&);
  void Script_node_7(const std_msgs::String::ConstPtr&);
  bool manner_1 = false, manner_2 = false, manner_3 = false, manner_4 = false, manner_5 = false, manner_6 = false, manner_7 = false;

private:
  ros::Subscriber sub[7];
};

extern Script_subscriber* subscriber;

#endif
