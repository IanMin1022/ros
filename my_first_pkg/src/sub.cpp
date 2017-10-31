#include "ros/ros.h"
#include "sub.h"
#include <cmath>
#include "std_msgs/String.h"
#include <stdio.h>
#include <string.h>

Sub* sub;

void Sub::chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  //yas = msg
}

void Sub::parameter() {
  ROS_INFO("%s",mm);
	//subs = nh.subscribe("chatter1", 100, &Sub::chatterCallback, this);
	// ROS_INFO("SUBSCRIBED");
}

void Sub::subscribe(ros::NodeHandle& nh) {
  //ROS_INFO("I heard(copy): [34]");
	//subs = nh.subscribe("chatter1", 100, &Sub::chatterCallback, this);

  //ROS_INFO("Let's see");

	// ROS_INFO("SUBSCRIBED");
}
