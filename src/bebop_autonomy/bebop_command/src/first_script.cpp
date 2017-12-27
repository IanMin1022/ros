#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Script_publisher.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nice_reader");

  ros::NodeHandle nh;
  script = new Script();

  script->advertise(nh);

  ros::Rate loop_rate(1);
  loop_rate.sleep();
  // Command is TAKE_OFF LAND FLIP_FORWARD FLIP_BACKWARD FLIP_LEFT FLIP_RIGHT UPDOWN SIDE
  // Make a time function so that you can know the whole function time****
  // -180 < yaw < 180
  if (ros::ok())
  {
    ros::spinOnce();

    script->script_1("TAKE_OFF");
    script->script_2("TAKE_OFF");
    script->script_3("TAKE_OFF");
    script->script_4("TAKE_OFF");
    script->script_5("TAKE_OFF");
    script->script_6("TAKE_OFF");
    script->script_7("TAKE_OFF");
    script->timer(3);
    ROS_INFO("start");
    script->script_1("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_2("0 0 0.6 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(7);
    ROS_INFO("start");
    script->script_1("0 0 0 0");
    script->script_2("0 0 1.2 90");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(12);
    ROS_INFO("start");
    script->script_1("0 0 0 0");
    script->script_2("0 0 0.6 90");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(16);
/*
    script->script_1("0 0 0 0");
    script->script_2("0 0 0.6 90");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(22);

    script->script_1("0 0 0 0");
    script->script_2("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(16);

    script->script_1("0 0 0 0");
    script->script_2("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(19);

    script->script_1("0 0 0 0");
    script->script_2("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(22);

    script->script_1("0 0 0 0");
    script->script_2("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(25);

    script->script_1("0 0 0 0");
    script->script_2("0 0 0 0");
    script->script_3("0 0 0 0");
    script->script_4("0 0 0 0");
    script->script_5("0 0 0 0");
    script->script_6("0 0 0 0");
    script->script_7("0 0 0 0");
    script->timer(27);
*/
    script->script_1("LAND");
    script->script_2("LAND");
    script->script_3("LAND");
    script->script_4("LAND");
    script->script_5("LAND");
    script->script_6("LAND");
    script->script_7("LAND");
    script->timer(20);


  }
  delete script;

  return 0;
}
