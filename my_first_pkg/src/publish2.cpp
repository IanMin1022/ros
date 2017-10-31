#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker2");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter2", 1);

  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;

    std::string msg1;
    getline(std::cin, msg1, '\n');
    std::stringstream ss;
    //std::scanf("%s", msg1);
    ss << msg1;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
