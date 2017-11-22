#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "commander");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub_1 = nh.advertise<std_msgs::String>("Script_1", 1000);

  ros::Rate loop_rate(1);
  loop_rate.sleep();
  // Command is TAKE_OFF LAND FLIP_FORWARD FLIP_BACKWARD FLIP_LEFT FLIP_RIGHT
  // Make a time function so that you can know the whole function time****
  if (ros::ok())
  {
    ros::spinOnce();
    std_msgs::String send_1;
    std::stringstream msg_1;

    msg_1 << "TAKE_OFF";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(3).sleep();

    msg_1 << "0 5 0 0";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(1).sleep();

    msg_1 << "0 -5 0 0";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(2).sleep();

    msg_1 << "0 5 0 0";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(1).sleep();

    msg_1 << "FLIP_FORWARD";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(2).sleep();
    
    msg_1 << "LAND";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");
    ros::Duration(2).sleep();
  }

  return 0;
}
