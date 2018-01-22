#include "Control.h"
#include "Script_publisher.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sstream>
#include <std_msgs/UInt32.h>
#include <string>

Script *script;
// 스크립트가 시작되는 걸 알려주기 위한 함수
void Script::clocker(const std_msgs::UInt32::ConstPtr &msg) {
  if (msg->data == 0)
    script_flag = true;
}

// 메인 함수로부터 프로그램이 구동되었다는 정보를 받아드리기 위한 함수
void Script::subscribe(ros::NodeHandle &nh) {
  super_sub = nh.subscribe("/current_time", 100, &Script::clocker, this);
}

// 스크립트를 읽은 후 동적 제어부로 전송 준비하는 함수
void Script::advertise(ros::NodeHandle &nh) {
  script_pub[0] = nh.advertise<std_msgs::String>("/Script_1", 100);
  script_pub[1] = nh.advertise<std_msgs::String>("/Script_2", 100);
  script_pub[2] = nh.advertise<std_msgs::String>("/Script_3", 100);
  script_pub[3] = nh.advertise<std_msgs::String>("/Script_4", 100);
  script_pub[4] = nh.advertise<std_msgs::String>("/Script_5", 100);
  script_pub[5] = nh.advertise<std_msgs::String>("/Script_6", 100);
  script_pub[6] = nh.advertise<std_msgs::String>("/Script_7", 100);
}

// ROS마스터로부터 ROS시간을 받아드리기 위한 함수
void Script::timer(float input_time) {
  float time_gap = input_time - old_time;
  old_time = input_time;

  if (ros::ok())
    ros::Duration(time_gap).sleep();
}

// 스크립트를 동적 제어부로 전송하는 함수
void Script::script_1(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[0].publish(send);
}

void Script::script_2(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[1].publish(send);
}
void Script::script_3(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[2].publish(send);
}
void Script::script_4(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[3].publish(send);
}
void Script::script_5(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[4].publish(send);
}
void Script::script_6(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[5].publish(send);
}

void Script::script_7(const char *input) {
  std::stringstream msg;
  msg << input;
  send.data = msg.str();
  script_pub[6].publish(send);
}
