#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("chatter1", 1000, chatterCallback);
  ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatterCallback);

  ros::spin();

  return 0;
}
