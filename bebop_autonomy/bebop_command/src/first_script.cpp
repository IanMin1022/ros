#include "ros/ros.h"
#include "Control.h"
#include "std_msgs/String.h"
#include <std_msgs/Empty.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Script_publisher.h"

bool script_flag = false;

/******************************************Command***********************************************
    NAME          |     TIME     |     DESCRIPTION
-------------------------------------------------------------------------------------------------
  TAKE_OFF        |   3000(ms)   |
  LAND            |   3000(ms)   |
  FLIP_FORWARD    |   1000(ms)   |
  FLIP_BACKWARD   |   1000(ms)   |
  FLIP_LEFT       |   1000(ms)   |
  FLIP_RIGHT      |   1000(ms)   |
  UPDOWN_GREET    |     35(ms)   |    tilt to forward
  UPDOWN_x        |   80*x(ms)   |    tilt to forward and backward (e.g. UPDOWN_1, UPDOWN_2, max 6)
  SIDE_LEFT       |     35(ms)   |    tilt once to left
  SIDE_RIGHT      |     35(ms)   |    tilt once to right
  SIDE_x          |   80*x(ms)   |    tilt to side (e.g. SIDE_1, SIDE_2, max 6)

  *****   -180 < yaw < 180    :  0  is ahead to forward   *******
************************************************************************************************/

void write_scrip_here(void) {
  /* Take Off */
    script->script_1("TAKE_OFF");
    script->script_2("TAKE_OFF");
    script->script_3("TAKE_OFF");
    script->script_4("TAKE_OFF");
    script->script_5("TAKE_OFF");
    script->script_6("TAKE_OFF");
    script->script_7("TAKE_OFF");
    script->timer(4);

  /* Satrt_Hovering */
    script->script_1("1 0.5 2 0");
    script->script_2("1 0.5 2 0");
    script->script_3("-1 0.5 2 0");
    script->script_4("UPDOWN_6");
    script->script_5("2 -2.5 2 0");
    script->script_6("0 -2.5 2 0");
    script->script_7("-2 -2.5 2 0");
    script->timer(7);

  /* Moving */
  /*  script->script_1("0 2.5 1.5 0");
    script->script_2("-2.331438 1.887961 1.5 0");
    script->script_3("-2.934443 -0.623735 2.1 0");
    script->script_4("-1.361971 -2.673020 1.5 0");
    script->script_5("1.22021 -2.740636 1.5 0");
    script->script_6("2.897777 -0.776457 2.1 0");
    script->script_7("2.427051 1.763356 1.5 0");
    script->timer(9.0);
    */
  /* Making the Circle
    script->script_1("0 2.5 1.5 0");
    script->script_2("-1.942865 1.573301 1.5 0");

    script->timer(9.0);

    script->script_1("0 2.5 1.5 0");

    script->timer(9.0);
   */

  /* Landing */
    script->script_1("LAND");
    script->script_2("LAND");
    script->script_3("LAND");
    script->script_4("LAND");
    script->script_5("LAND");
    script->script_6("LAND");
    script->script_7("LAND");
    script->timer(10);

    /*
    script->script_1("1.1 -0.9 1 0");
    script->script_2("2 0 1 0");
    script->script_3("0.6 0.5 1 0");
    script->script_4("-1 0.7 1 0");
    script->script_5("-0.2 -0.9 1 0");
    script->script_6("-1.5 -0.98 1 0");
    script->script_7("-2 0.3 1 0");
    script->timer(9);

    script->script_1("-0.2 -0.9 1 0");
    script->script_2("1.1 -0.9 1 0");
    script->script_3("2 0 1 0");
    script->script_4("0.6 0.5 1 0");
    script->script_5("-1.5 -0.98 1 0");
    script->script_6("-2 0.3 1 0");
    script->script_7("-1 0.7 1 0");
    script->timer(12);

    script->script_1("LAND");
    script->script_2("LAND");
    script->script_3("LAND");
    script->script_4("LAND");
    script->script_5("LAND");
    script->script_6("LAND");
    script->script_7("LAND");
    script->timer(12);
    */
}

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
  const char*  q_sign = msg->data.c_str();
  std::istringstream tmp(q_sign);
  int int_tmp;
  tmp >> int_tmp;

  if ( int_tmp == 0 ) script_flag = true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "First_script");
  bool next_turn = false;
  int flattrim = 0;
  std_msgs::Empty m;
  ros::NodeHandle nh;
  ros::Publisher pub[9];

  script = new Script();
  script->advertise(nh);
  pub[0] = nh.advertise<std_msgs::Empty>("bebop_1/flattrim", 1);
  pub[1] = nh.advertise<std_msgs::Empty>("bebop_2/flattrim", 1);
  pub[2] = nh.advertise<std_msgs::Empty>("bebop_3/flattrim", 1);
  pub[3] = nh.advertise<std_msgs::Empty>("bebop_4/flattrim", 1);
  pub[4] = nh.advertise<std_msgs::Empty>("bebop_5/flattrim", 1);
  pub[5] = nh.advertise<std_msgs::Empty>("bebop_6/flattrim", 1);
  pub[6] = nh.advertise<std_msgs::Empty>("bebop_7/flattrim", 1);

  ros::Subscriber sub = nh.subscribe("on_air", 10, chatterCallback);
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

    if ( script_flag ) {
      write_scrip_here();
      script_flag = false;
      next_turn = true;
    }
    else if ( next_turn ) {
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      if (ros::ok()) ros::Duration(1).sleep();
    }

    loop_rate.sleep();
  }
  delete script;

  return 0;
}
