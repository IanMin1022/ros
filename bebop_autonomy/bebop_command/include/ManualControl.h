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
#define HOME 8

class ManualControl {
public:
	void position_control_1();
	void doMisc_1(short);
	void doMisc_2(short);
	void doFlip_1(short);
	void doFlip_2(short);
	void advertise_1(ros::NodeHandle&);
	void advertise_2(ros::NodeHandle&);
	void key_1(const char* transmit);
	void key_2(const char* transmit);
	double x_des[7], y_des[7], z_des[7], yaw_des[7];
	double x[7], y[7], z[7], yaw[7];
//	void test();

private:
	ros::Publisher pub_1[9];
	ros::Publisher pub_2[9];
	double x_gap = 0, y_gap = 0, z_gap = 0, yaw_gap = 0;
	double x_gap_old = 0, y_gap_old = 0;
	double x_speed = 0;
	double y_speed = 0;
	double x_speed_old = 0;
	double y_speed_old = 0;
	double P_x_gain = 0, P_y_gain = 0;
	double D_x_gain = 0, D_y_gain = 0;
	double x_value = 0, y_value = 0;
	double dt = 0.05;
	double speed = 0.7;
	double rotSpeed = 0.7;
	geometry_msgs::Twist last;
};

extern ManualControl* control;

#endif
