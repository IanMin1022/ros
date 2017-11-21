#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <iostream>
#include <sstream>

void script(std_msgs::String send)
{
  std::istringstream devide(transmit); // 브라켓 마다 나눠지게 만들기

	std::string temp;
	devide >> temp;
}

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

  if (ros::ok())
  {
    ros::spinOnce();

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
