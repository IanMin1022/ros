#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker2");
  ros::NodeHandle n;

  ros::Publisher chatter_pub_1 = n.advertise<std_msgs::String>("chatter1", 1);
  ros::Publisher chatter_pub_2 = n.advertise<std_msgs::String>("chatter2", 1);

  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
    std_msgs::String msg1;

    std::string msg_1;
    std::string empty_1;
    getline(std::cin, empty_1, '<');
    getline(std::cin, msg_1, '>');

    std::string msg_2;
    std::string empty_2;
    getline(std::cin, empty_2, '<');
    getline(std::cin, msg_2, '>');

    std::string next_line;
    getline(std::cin, next_line, '\n');

    std::stringstream ss;
    std::stringstream ss_1;
    //std::scanf("%s", msg1);
    ss << msg_1;
    ss_1 << msg_2;
    msg.data = ss.str();
    msg1.data = ss_1.str();

    //ROS_INFO("%s", msg.data.c_str());
    //ROS_INFO("%s", msg1.data.c_str());

    chatter_pub_1.publish(msg);
    chatter_pub_2.publish(msg1);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
