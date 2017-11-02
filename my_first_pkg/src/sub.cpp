#include "ros/ros.h"
#include "my_first_pkg/sub.h"
#include <cmath>
#include "std_msgs/String.h"
#include <stdio.h>
#include <string.h>

Sub* sub;

void Sub::parameter() {
  //ROS_INFO("%s",mm);
	//subs = nh.subscribe("chatter1", 100, &Sub::chatterCallback, this);
  //const char* jack = mm;
  //if(mm != NULL) //enabled = true;
  if(!enabled)
  {
    return;
  }
  else
  {
      ROS_INFO("SUBSCRIBED, %d", ye);
      enabled = false;
  }

}

void Sub::subscribe(ros::NodeHandle& nh) {
  //ROS_INFO("I heard(copy): [34]");
	//subs = nh.subscribe("chatter1", 100, &Sub::chatterCallback, this);

  //ROS_INFO("Let's see");

	// ROS_INFO("SUBSCRIBED");
}
