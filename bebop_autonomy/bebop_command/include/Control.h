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
  void position_control_1();
  void position_control_2();
  void position_control_3();
  void position_control_4();
  void position_control_5();
  void position_control_6();
  void position_control_7();

  void doMisc_1(short);
  void doMisc_2(short);
  void doMisc_3(short);
  void doMisc_4(short);
  void doMisc_5(short);
  void doMisc_6(short);
  void doMisc_7(short);

  void doFlip_1(short);
  void doFlip_2(short);
  void doFlip_3(short);
  void doFlip_4(short);
  void doFlip_5(short);
  void doFlip_6(short);
  void doFlip_7(short);

  void LeftNRight_1();
  void LeftNRight_2();
  void LeftNRight_3();
  void LeftNRight_4();
  void LeftNRight_5();
  void LeftNRight_6();
  void LeftNRight_7();

  void UpDown_1();
  void UpDown_2();
  void UpDown_3();
  void UpDown_4();
  void UpDown_5();
  void UpDown_6();
  void UpDown_7();

  void advertise(ros::NodeHandle &);

  void key_1(const char *);
  void key_2(const char *);
  void key_3(const char *);
  void key_4(const char *);
  void key_5(const char *);
  void key_6(const char *);
  void key_7(const char *);

  double x_des[7], y_des[7], z_des[7], yaw_des[7];
  double x[7], y[7], z[7], yaw[7];
  int takeoffNland_counter = 200, motion_counter = 200;
  bool TakeoffFlag_1 = false, TakeoffFlag_2 = false, TakeoffFlag_3 = false,
       TakeoffFlag_4 = false, TakeoffFlag_5 = false, TakeoffFlag_6 = false,
       TakeoffFlag_7 = false;
  bool LandFlag_1 = false, LandFlag_2 = false, LandFlag_3 = false,
       LandFlag_4 = false, LandFlag_5 = false, LandFlag_6 = false,
       LandFlag_7 = false;
  bool SideFlag_1 = false, SideFlag_2 = false, SideFlag_3 = false,
       SideFlag_4 = false, SideFlag_5 = false, SideFlag_6 = false,
       SideFlag_7 = false;
  bool UpDownFlag_1 = false, UpDownFlag_2 = false, UpDownFlag_3 = false,
       UpDownFlag_4 = false, UpDownFlag_5 = false, UpDownFlag_6 = false,
       UpDownFlag_7 = false;
  bool direction = true, direction_1 = true, direction_2 = true,
       direction_3 = true, direction_4 = true, direction_5 = true,
       direction_6 = true, direction_7 = true;
  int repeat = 0, repeat_1 = 0, repeat_2 = 0, repeat_3 = 0, repeat_4 = 0,
      repeat_5 = 0, repeat_6 = 0, repeat_7 = 0;
  double side_1 = 0, side_2 = 0, side_3 = 0, side_4 = 0, side_5 = 0, side_6 = 0,
         side_7 = 0;
  double updown_1 = 0, updown_2 = 0, updown_3 = 0, updown_4 = 0, updown_5 = 0,
         updown_6 = 0, updown_7 = 0;

private:
  ros::Publisher pub_1[9];
  ros::Publisher pub_2[9];
  ros::Publisher pub_3[9];
  ros::Publisher pub_4[9];
  ros::Publisher pub_5[9];
  ros::Publisher pub_6[9];
  ros::Publisher pub_7[9];

  double P_control_x[7], P_control_y[7], P_control_z[7], P_control_yaw[7];
  double I_control_x[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_y[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_z[7] = {0, 0, 0, 0, 0, 0, 0};
  double I_control_yaw[7] = {0, 0, 0, 0, 0, 0, 0};
  double D_control_x[7], D_control_y[7], D_control_z[7], D_control_yaw[7];

  double x_gap[7], y_gap[7], z_gap[7], yaw_gap[7];
  double x_speed_old[7], y_speed_old[7], z_gap_old[7], yaw_gap_old[7];
  double x_speed[7];
  double y_speed[7];

  geometry_msgs::Twist last_1, last_2, last_3, last_4, last_5, last_6, last_7;
};

extern Control *control;

#endif
