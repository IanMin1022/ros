#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sub.h"

Sub what;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  const char* jack = msg->data.c_str();
  ROS_INFO("I heard: [%s]", jack);
  what.mm = jack;
  what.parameter();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("chatter1", 1000, chatterCallback);
  ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatterCallback);

  ros::Rate loop_rate(1000);

  while( ros::ok() ) {
		ros::spinOnce();
    sub->subscribe(n);

    loop_rate.sleep();
  }

  //ros::spin();

  return 0;
}
