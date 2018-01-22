#include "Camera.h"
#include "Control.h"
#include "Script_subscriber.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sstream>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt32.h>
#include <stdio.h>
#include <string.h>

int performance_time = 1;

void timeset(const std_msgs::Float32::ConstPtr &msg) {
  performance_time = msg->data * 100;
}

int main(int argc, char **argv) {
  int show_time = -30;
  ros::init(argc, argv, "node_master");
  ros::NodeHandle nh;
  // ros::NodeHandle local_nh("~");
  ros::Timer CheckTime = nh.createTimer(ros::Duration(0.05), Motion_timer);

  ros::Publisher time_pub = nh.advertise<std_msgs::UInt32>("/current_time", 10);

  control = new Control();
  subscriber = new Script_subscriber();
  camera_node = new Camera_node();

  control->advertise(nh);

  subscriber->subscribe(nh);
  camera_node->subscribe(nh);

  ros::Rate loop_rate(100);

  ros::Subscriber sub = nh.subscribe("/duration_time", 10, timeset);

  while (ros::ok()) {
    ros::spinOnce();
    if (show_time < performance_time) {
      show_time++;
      std_msgs::UInt32 msg;
      msg.data = show_time;
      time_pub.publish(msg);
      if (performance_time != 1) {
        sub.shutdown();
      }
    }
    loop_rate.sleep();
  }

  ros::shutdown();
  delete camera_node;
  delete subscriber;
  delete control;
  return 0;
}
