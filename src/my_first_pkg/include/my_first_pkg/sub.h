#ifndef SUB_H
#define SUB_H

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/NavSatFix.h>
#include <stdio.h>
#include <string.h>

class Sub {
public:

  void chatterCallback(const std_msgs::String::ConstPtr& msg);
  void parameter(void);
	void subscribe(ros::NodeHandle&);
  const char* mm;

private:
  //const std_msgs::String::ConstPtr yas;
	ros::Subscriber subs;
  double ye = 7;
  bool enabled = true;
};

extern Sub* sub;

#endif
