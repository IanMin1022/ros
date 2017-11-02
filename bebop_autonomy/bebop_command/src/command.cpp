#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "commander");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub_1 = nh.advertise<std_msgs::String>("Command_1", 1);
  ros::Publisher chatter_pub_2 = nh.advertise<std_msgs::String>("Command_2", 1);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    ros::spinOnce();
    std_msgs::String send_1;
    std_msgs::String send_2;

    std::string msg_1;
    std::string empty_1;
    getline(std::cin, empty_1, '<');
    getline(std::cin, msg_1, '>');

    std::string msg_2;
    std::string empty_2;
    getline(std::cin, empty_2, '<');
    getline(std::cin, msg_2, '>');

    //std::string next_line;
    //getline(std::cin, next_line, '\n');

    //std::string next_line2;
    //getline(std::cin, next_line2, '\n');

    std::stringstream transfer_1;
    std::stringstream transfer_2;
    //std::scanf("%s", msg1);
    transfer_1 << msg_1;
    transfer_2 << msg_2;
    send_1.data = transfer_1.str();
    send_2.data = transfer_2.str();

    //ROS_INFO("%s", msg.data.c_str());
    //ROS_INFO("%s", msg1.data.c_str());

    chatter_pub_1.publish(send_1);
    chatter_pub_2.publish(send_2);

    loop_rate.sleep();
  }

  return 0;
}
