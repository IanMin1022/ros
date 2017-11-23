#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ManualControl.h"
#include "Script_publisher.h"
#include <string>
#include <iostream>
#include <sstream>

Script* script;

void Script::advertise(ros::NodeHandle& nh)
{
  script_pub[0] = nh.advertise<std_msgs::String>("Script_1", 1000);/*
  script_pub[1] = nh.advertise<std_msgs::String>("Script_2", 1000);
  script_pub[2] = nh.advertise<std_msgs::String>("Script_3", 1000);
  script_pub[3] = nh.advertise<std_msgs::String>("Script_4", 1000);
  script_pub[4] = nh.advertise<std_msgs::String>("Script_5", 1000);
  script_pub[5] = nh.advertise<std_msgs::String>("Script_6", 1000);
  script_pub[6] = nh.advertise<std_msgs::String>("Script_7", 1000);*/
}

void Script::timer(float input_time)
{
  float time_gap = input_time - old_time;
  old_time = input_time;
  ros::Duration(time_gap).sleep();
}


void Script::script_1(const char* input)
{
  msg_1 << input;
  send_1.data = msg_1.str();
  script_pub[0].publish(send_1);
  msg_1.str("");
}
