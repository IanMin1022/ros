#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Script");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub_1 = nh.advertise<std_msgs::String>("Camera", 1000);
  //ros::Publisher chatter_pub_2 = nh.advertise<std_msgs::String>("Command_2", 1);

  std_msgs::String script_1;

  std_msgs::String script_send_1;

  std::stringstream transfer_1;

  ros::Rate loop_rate(100);

  while (ros::ok())
  {
    ros::spinOnce();
    std_msgs::String send_1;

    std::stringstream msg_1;
    msg_1 << "0 0 0 0";
    send_1.data = msg_1.str();
    ROS_INFO("%s", send_1.data.c_str());
    chatter_pub_1.publish(send_1);
    msg_1.str("");

    loop_rate.sleep();
  }

  return 0;
}
