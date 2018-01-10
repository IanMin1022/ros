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
  void script_2(const char*);
  void script_3(const char*);
  void script_4(const char*);
  void script_5(const char*);
  void script_6(const char*);
  void script_7(const char*);
  void advertise(ros::NodeHandle&);
  void timer(float);
  void repeater(float);
  ros::Publisher script_pub[7];
  float old_time = 0;

  std_msgs::String send;
  std::stringstream msg;

  int stop = 0;

private:

};

extern Script* script;

#endif
