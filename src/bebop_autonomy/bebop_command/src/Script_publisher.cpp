#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Control.h"
#include "Script_publisher.h"
#include <string>
#include <iostream>
#include <sstream>

Script* script;

void Script::advertise(ros::NodeHandle& nh) {
  script_pub[0] = nh.advertise<std_msgs::String>("Script_1", 100);
  script_pub[1] = nh.advertise<std_msgs::String>("Script_2", 100);
  script_pub[2] = nh.advertise<std_msgs::String>("Script_3", 100);
  script_pub[3] = nh.advertise<std_msgs::String>("Script_4", 100);
  script_pub[4] = nh.advertise<std_msgs::String>("Script_5", 100);
  script_pub[5] = nh.advertise<std_msgs::String>("Script_6", 100);
  script_pub[6] = nh.advertise<std_msgs::String>("Script_7", 100);
}

void Script::timer(float input_time) {
  float time_gap = input_time - old_time;
  old_time = input_time;

  ros::Duration(time_gap).sleep();
}


void Script::script_1(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[0].publish(send);
  msg.str("");
}

void Script::script_2(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[1].publish(send);
  msg.str("");
}
void Script::script_3(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[2].publish(send);
  msg.str("");
}
void Script::script_4(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[3].publish(send);
  msg.str("");
}
void Script::script_5(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[4].publish(send);
  msg.str("");
}
void Script::script_6(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[5].publish(send);
  msg.str("");
}

void Script::script_7(const char* input) {
  msg << input;
  send.data = msg.str();
  script_pub[6].publish(send);
  msg.str("");
}
