#ifndef __MANUAL_H__
#define __MANUAL_H__

//#include "Input.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#define VELOCITY 0
#define TAKEOFF 1
#define LAND 2
#define RESET 3
#define CAMERA 4
#define SNAPSHOT 5
#define RECORD 6
#define FLIP 7

void Motion_timer(const ros::TimerEvent &event);

class Control {
public:
  void position_control(short, ros::Publisher);

  void key(short, const char *, ros::Publisher);

  void doMisc(short, short, ros::Publisher, ros::Publisher);
  void doFlip(short, ros::Publisher);
  void LeftNRight(short);
  void UpDown(short);

  void advertise(ros::NodeHandle &);

  double x_des[7], y_des[7], z_des[7], yaw_des[7];
  double x[7], y[7], z[7], yaw[7];
  int takeoffNland_counter = 200;
  int TakeoffFlag[7] = {0, 0, 0, 0, 0, 0, 0};
  int LandFlag[7] = {0, 0, 0, 0, 0, 0, 0};
  int SideFlag[7] = {0, 0, 0, 0, 0, 0, 0};
  int UpDownFlag[7] = {0, 0, 0, 0, 0, 0, 0};
  int direction[7];
  int repeat[7];
  int repeat_count[7] = {0, 0, 0, 0, 0, 0, 0};
  int manner[7];
  double side_1 = 0, side_2 = 0, side_3 = 0, side_4 = 0, side_5 = 0, side_6 = 0,
         side_7 = 0;

  ros::Publisher pub_1[9];
  ros::Publisher pub_2[9];
  ros::Publisher pub_3[9];
  ros::Publisher pub_4[9];
  ros::Publisher pub_5[9];
  ros::Publisher pub_6[9];
  ros::Publisher pub_7[9];

private:
  double I_control_x[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_y[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_z[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_yaw[7] = {0, 0, 0, 0, 0, 0, 0};

  double x_speed_old[7], y_speed_old[7], z_gap_old[7], yaw_gap_old[7];

  double x_tmp[7], y_tmp[7];
  int turn_switch[7];
};

extern Control *control;

#endif
