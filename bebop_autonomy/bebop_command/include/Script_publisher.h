#ifndef __PUBLISH_H__
#define __PUBLISH_H__

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>

class Script {
public:
  void script_1(const char*);
  void advertise(ros::NodeHandle&);
  void timer(float);
  ros::Publisher script_pub[7];
  float old_time = 0;

  std_msgs::String send_1;
  std::stringstream msg_1;

private:

};

extern Script* script;

#endif
