#include "ros/ros.h"
#include "Control.h"
#include <std_msgs/Empty.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Script_publisher.h"

/******************************************Command***********************************************
    NAME          |     TIME     |     DESCRIPTION
-------------------------------------------------------------------------------------------------
  TAKE_OFF        |   3000(ms)   |
  LAND            |   3000(ms)   |
  FLIP_FORWARD    |   1000(ms)   |
  FLIP_BACKWARD   |   1000(ms)   |
  FLIP_LEFT       |   1000(ms)   |
  FLIP_RIGHT      |   1000(ms)   |
  UPDOWN_GREET    |    250(ms)   |    tilt to forward
  UPDOWN_x        |  800*x(ms)   |    tilt to forward and backward (e.g. UPDOWN_1, UPDOWN_2, max 8)
  SIDE_LEFT       |    300(ms)   |    tilt once to left
  SIDE_RIGHT      |    300(ms)   |    tilt once to right
  SIDE_x          |  800*x(ms)   |    tilt to side (e.g. SIDE_1, SIDE_2, max 8)

  *****   -180 < yaw < 180    :  0  is ahead to forward   *******
************************************************************************************************/

void write_scrip_here(void) {
  /* Take Off */
      script->timer(0);
      script->script_1("TAKE_OFF");
      script->script_2("TAKE_OFF");
      script->script_3("TAKE_OFF");
      script->script_4("TAKE_OFF");
      script->script_5("TAKE_OFF");
      script->script_6("TAKE_OFF");
      script->script_7("TAKE_OFF");

    /* Take Off */
      script->timer(3.0);
      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");

    /* Take Off */
      script->timer(5.0);
      script->script_1("UPDOWN_GREET");
      script->script_2("SIDE_8");
      script->script_3("SIDE_8");
      script->script_4("SIDE_8");
      script->script_5("SIDE_8");
      script->script_6("SIDE_8");
      script->script_7("SIDE_8");


    /* Landing */
      script->timer(12.0);
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Second_script");
  int flattrim = 0;
  bool checksome = false;
  std_msgs::Empty m;
  ros::NodeHandle nh;
  ros::Publisher pub[9];

  script = new Script();
  script->advertise(nh);
  script->subscribe(nh);
  pub[0] = nh.advertise<std_msgs::Empty>("/bebop_1/flattrim", 1);
  pub[1] = nh.advertise<std_msgs::Empty>("/bebop_2/flattrim", 1);
  pub[2] = nh.advertise<std_msgs::Empty>("/bebop_3/flattrim", 1);
  pub[3] = nh.advertise<std_msgs::Empty>("/bebop_4/flattrim", 1);
  pub[4] = nh.advertise<std_msgs::Empty>("/bebop_5/flattrim", 1);
  pub[5] = nh.advertise<std_msgs::Empty>("/bebop_6/flattrim", 1);
  pub[6] = nh.advertise<std_msgs::Empty>("/bebop_7/flattrim", 1);

  ros::Rate loop_rate(30);

  while (ros::ok())
  {
    ros::spinOnce();

    if ( flattrim < 10) {
      pub[0].publish(m);
      pub[1].publish(m);
      pub[2].publish(m);
      pub[3].publish(m);
      pub[4].publish(m);
      pub[5].publish(m);
      pub[6].publish(m);
      flattrim++;
    }

    if ( script->script_flag ) {
      script->super_sub.shutdown();
      write_scrip_here();
      ros::Duration(3).sleep();
      script->script_flag = false;
      checksome = true;
    }
    if ( checksome ) {
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      if (ros::ok()) ros::Duration(2).sleep();
    }

    loop_rate.sleep();
  }
  delete script;

  return 0;
}
