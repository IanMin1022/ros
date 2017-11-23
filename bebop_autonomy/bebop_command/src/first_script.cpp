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

  script -> advertise(nh);

  ros::Rate loop_rate(1);
  loop_rate.sleep();
  // Command is TAKE_OFF LAND FLIP_FORWARD FLIP_BACKWARD FLIP_LEFT FLIP_RIGHT
  // Make a time function so that you can know the whole function time****
  if (ros::ok())
  {
    ros::spinOnce();

    script -> script_1("TAKE_OFF");
    script -> timer(5);

    script -> script_1("5 0 0 0");
    script -> timer(5.3);

    script -> script_1("-5 0 0 0");
    script -> timer(5.7);

    script -> script_1("5 0 0 0");
    script -> timer(6);

    script -> script_1("FLIP_FORWARD");
    script -> timer(10);

    script -> script_1("LAND");
    script -> timer(18);
  }
  delete script;

  return 0;
}
