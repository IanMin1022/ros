#include "ros/ros.h"
#include "std_msgs/String.h"
#include "my_first_pkg/sub.h"

Sub what;

void chatterCallback_1(const std_msgs::String::ConstPtr& msg)
{
  const char* jack = msg->data.c_str();
  ROS_INFO("fisrt: [%s]", jack);
  what.mm = jack;
}

void chatterCallback_2(const std_msgs::String::ConstPtr& msg)
{
  const char* jack = msg->data.c_str();
  ROS_INFO("second: [%s]", jack);
  what.mm = jack;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("chatter1", 1000, chatterCallback_1);
  ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatterCallback_2);

  ros::Rate loop_rate(10);

  while( ros::ok() ) {
		ros::spinOnce();
    sub->subscribe(n);

    sub->parameter();
    if (what.mm != NULL)
    {
      what.mm = NULL;
      ROS_INFO("%s",what.mm);
    }
    loop_rate.sleep();
  }

  //ros::spin();

  return 0;
}
