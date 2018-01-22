#include "Control.h"
#include "Script_publisher.h"
#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <string>

bool stop_secret = false;

// 비상 정지 작동
void stopper(const std_msgs::Bool::ConstPtr &msg) { stop_secret = msg->data; }

int main(int argc, char **argv) {
  ros::init(argc, argv, "Emergency");

  ros::NodeHandle nh;

  script = new Script();
  script->advertise(nh);
  ros::Subscriber sub = nh.subscribe("/stop_it", 10, stopper);

  ros::Rate loop_rate(30);

  while (ros::ok()) {
    ros::spinOnce();
    if (stop_secret) {
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      ros::Duration(5).sleep();
      system("terminator --new-tab -H --execute killall stop &");
    }
    loop_rate.sleep();
  }
  delete script;

  return 0;
}
