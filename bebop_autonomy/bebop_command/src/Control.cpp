#include "Control.h"
#include "Script_subscriber.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#define Flip_forward 1
#define Flip_backword 2
#define FLip_left 3
#define FLip_right 4
#define DO_LAND 5
#define DO_TAKEOFF 6
#define DO_RESET 8
#define SIDE 10
#define UPDOWN 11

#define Kp_x 0.6
double Ki_x = 0.0001;
#define Kd_x 2.65					// 2.35

#define Kp_y 0.6
double Ki_y = 0.0001;
#define Kd_y 2.65					// 2.35

#define Kp_z 1.5
double Ki_z = 0.0003;
#define Kd_z 0.97

#define Kp_yaw 0.043
#define Ki_yaw 0
#define Kd_yaw 0.024

#define dt 0.05

Control* control;

void Motion_timer(const ros::TimerEvent& event) {
	if ( control->TakeoffNLandFlag ) {
		if ( control->TakeoffFlag_1 ) {
			control->doMisc_1(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_2 ) {
			control->doMisc_2(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_3 ) {
			control->doMisc_3(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_4 ) {
			control->doMisc_4(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_5 ) {
			control->doMisc_5(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_6 ) {
			control->doMisc_6(DO_TAKEOFF);
		}

		if ( control->TakeoffFlag_7 ) {
			control->doMisc_7(DO_TAKEOFF);
		}

		if ( control->LandFlag_1 ) {
			control->doMisc_1(DO_LAND);
		}

		if ( control->LandFlag_2 ) {
			control->doMisc_2(DO_LAND);
		}

		if ( control->LandFlag_3 ) {
			control->doMisc_3(DO_LAND);
		}

		if ( control->LandFlag_4 ) {
			control->doMisc_4(DO_LAND);
		}

		if ( control->LandFlag_5 ) {
			control->doMisc_5(DO_LAND);
		}

		if ( control->LandFlag_6 ) {
			control->doMisc_6(DO_LAND);
		}

		if ( control->LandFlag_7 ) {
			control->doMisc_7(DO_LAND);
		}

		control->takeoffNland_counter++;
	}

	if ( control->MotionFlag ) {
		if ( control->SideFlag_1 ) {
			control->LeftNRight_1();
		}

		if ( control->SideFlag_2 ) {
			control->LeftNRight_2();
		}

		if ( control->SideFlag_3 ) {
			control->LeftNRight_3();
		}

		if ( control->SideFlag_4 ) {
			control->LeftNRight_4();
		}

		if ( control->SideFlag_5 ) {
			control->LeftNRight_5();
		}

		if ( control->SideFlag_6 ) {
			control->LeftNRight_6();
		}

		if ( control->SideFlag_7 ) {
			control->LeftNRight_7();
		}

		if ( control->UpDownFlag_1 ) {
			control->UpDown_1();
		}

		if ( control->UpDownFlag_2 ) {
			control->UpDown_2();
		}

		if ( control->UpDownFlag_3 ) {
			control->UpDown_3();
		}

		if ( control->UpDownFlag_4 ) {
			control->UpDown_4();
		}

		if ( control->UpDownFlag_5 ) {
			control->UpDown_5();
		}

		if ( control->UpDownFlag_6 ) {
			control->UpDown_6();
		}

		if ( control->UpDownFlag_7 ) {
			control->UpDown_7();
		}

		control->motion_counter++;
	}

	if ( Ki_x == 0 ) {
		if ( control->rest_timer > 20) {
			Ki_x = 0.0001;
			Ki_y = 0.0001;
			Ki_z = 0.0003;
		}
		control->rest_timer++;
	}
}

int Converter(const char* input) {
	char flip_forward = 'F';
	char flip_backward = 'B';
	char flip_left = 'E';
	char flip_right = 'I';
	char land = 'L';
	char take_off = 'T';
	char side = 'S';
	char updown = 'U';

	if (input[0] == 'F') {
		if (input[5] == flip_forward)	{
			return 1;
		}
		else if (input[5] == flip_backward)	{
			return 2;
		}
		else if (input[6] == flip_left)	{
			return 3;
		}
		else if (input[6] == flip_right) {
			return 4;
		}
	}
	else if (input[0] == land) {
		return 5;
	}
	else if (input[0] == take_off)	{
		return 6;
	}
	else if (input[0] == side)	{
		if (input[5] == 'L') {
			control->direction = true;
		}
		else if (input[5] == 'R') {
			control->direction = false;
		}
		else if (input[5] == '1') {
			control->repeat = 1;
		}
		else if (input[5] == '2') {
			control->repeat = 2;
		}
		else if (input[5] == '3') {
			control->repeat = 3;
		}
		else if (input[5] == '4') {
			control->repeat = 4;
		}
		else if (input[5] == '5') {
			control->repeat = 5;
		}
		else {
			control->repeat = 6;
		}
		return 10;
	}
	else if (input[0] == updown)	{
		if (input[7] == 'G') {
			control->repeat = 0;
		}
		else if (input[7] == '1') {
			control->repeat = 1;
		}
		else if (input[7] == '2') {
			control->repeat = 2;
		}
		else if (input[7] == '3') {
			control->repeat = 3;
		}
		else if (input[7] == '4') {
			control->repeat = 4;
		}
		else if (input[7] == '5') {
			control->repeat = 5;
		}
		else {
			control->repeat = 6;
		}
		return 11;
	}
	else	{
		return 0;
	}
}

double Deg2Rad(double deg) {
	return deg * M_PI / 180;
}

void Control::key_1(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_1(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_1(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_1(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_1(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_1 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_1 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_1 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_1 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_2(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_2(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_2(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_2(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_2(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_2 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_2 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_2 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_2 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_3(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_3(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_3(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_3(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_3(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_3 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_3 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_3 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_3 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_4(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_4(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_4(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_4(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_4(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_4 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_4 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_4 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_4 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_5(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_5(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_5(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_5(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_5(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_5 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_5 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_5 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_5 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_6(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_6(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_6(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_6(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_6(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_6 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_6 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_6 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_6 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::key_7(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_7(0);
			break;

		case 2:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_7(1);
			break;

		case 3:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_7(2);
			break;

		case 4:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			doFlip_7(3);
			break;

		case DO_LAND:
			control->TakeoffNLandFlag = true;
			control->LandFlag_7 = true;
			control->takeoffNland_counter = 0;
			break;

		case DO_TAKEOFF:
			control->TakeoffNLandFlag = true;
			control->TakeoffFlag_7 = true;
			control->takeoffNland_counter = 0;
			break;

		case SIDE:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->SideFlag_7 = true;
			control->motion_counter = 0;
			break;

		case UPDOWN:
			Ki_x = 0, Ki_y = 0, Ki_z = 0;
			control->MotionFlag = true;
			control->UpDownFlag_7 = true;
			control->motion_counter = 0;
			break;

		default:
			return;
		}
}

void Control::advertise(ros::NodeHandle& nh) {
	pub_1[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_1/cmd_vel", 1);
	pub_1[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_1/takeoff", 1);
	pub_1[LAND] = nh.advertise<std_msgs::Empty>("bebop_1/land", 1);
	pub_1[RESET] = nh.advertise<std_msgs::Empty>("bebop_1/reset", 1);
	pub_1[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_1/flip", 1);

	pub_2[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_2/cmd_vel", 1);
	pub_2[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_2/takeoff", 1);
	pub_2[LAND] = nh.advertise<std_msgs::Empty>("bebop_2/land", 1);
	pub_2[RESET] = nh.advertise<std_msgs::Empty>("bebop_2/reset", 1);
	pub_2[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_2/flip", 1);

	pub_3[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_3/cmd_vel", 1);
	pub_3[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_3/takeoff", 1);
	pub_3[LAND] = nh.advertise<std_msgs::Empty>("bebop_3/land", 1);
	pub_3[RESET] = nh.advertise<std_msgs::Empty>("bebop_3/reset", 1);
	pub_3[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_3/flip", 1);

	pub_4[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_4/cmd_vel", 1);
	pub_4[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_4/takeoff", 1);
	pub_4[LAND] = nh.advertise<std_msgs::Empty>("bebop_4/land", 1);
	pub_4[RESET] = nh.advertise<std_msgs::Empty>("bebop_4/reset", 1);
	pub_4[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_4/flip", 1);

	pub_5[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_5/cmd_vel", 1);
	pub_5[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_5/takeoff", 1);
	pub_5[LAND] = nh.advertise<std_msgs::Empty>("bebop_5/land", 1);
	pub_5[RESET] = nh.advertise<std_msgs::Empty>("bebop_5/reset", 1);
	pub_5[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_5/flip", 1);

	pub_6[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_6/cmd_vel", 1);
	pub_6[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_6/takeoff", 1);
	pub_6[LAND] = nh.advertise<std_msgs::Empty>("bebop_6/land", 1);
	pub_6[RESET] = nh.advertise<std_msgs::Empty>("bebop_6/reset", 1);
	pub_6[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_6/flip", 1);

	pub_7[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_7/cmd_vel", 1);
	pub_7[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_7/takeoff", 1);
	pub_7[LAND] = nh.advertise<std_msgs::Empty>("bebop_7/land", 1);
	pub_7[RESET] = nh.advertise<std_msgs::Empty>("bebop_7/reset", 1);
	pub_7[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_7/flip", 1);
}

// horizontal axis is x, vertical axis is y.
void Control::position_control_1() {
	x_gap[0] = x_des[0] - x[0]; // x is horizontal data from motive
	y_gap[0] = y_des[0] - y[0]; // y is axis to sky
	z_gap[0] = z_des[0] - z[0]; // z is vertical data from motive

	if ( abs(yaw_des[0] - yaw[0]) <=  180) 	yaw_gap[0] = yaw_des[0] - yaw[0];
	else {
		if ( yaw_des[0] >= yaw[0]) yaw_gap[0] = -yaw[0] - (360 - yaw_des[0]);
		else yaw_gap[0] = yaw_des[0] + (360 - yaw[0]);
	}

	// 0 <= speed <= 1
	// change yaw to fit in 0 - 360
	x_speed[0] = ( -sin(Deg2Rad(yaw[0])) * x_gap[0] + cos(Deg2Rad(yaw[0])) * y_gap[0] );
	y_speed[0] = ( -cos(Deg2Rad(yaw[0])) * x_gap[0] - sin(Deg2Rad(yaw[0])) * y_gap[0] );

	P_control_x[0] = Kp_x * x_speed[0];
	I_control_x[0] = I_control_x[0] + Ki_x * x_speed[0] * dt;
	D_control_x[0] = Kd_x * (x_speed[0] - x_speed_old[0]) / dt;

	P_control_y[0] = Kp_y * y_speed[0];
	I_control_y[0] = I_control_y[0] + Ki_y * y_speed[0] * dt;
	D_control_y[0] = Kd_y * (y_speed[0] - y_speed_old[0]) / dt;

	P_control_z[0] = Kp_z * z_gap[0];
	I_control_z[0] = I_control_z[0] + Ki_z * z_gap[0] * dt;
	D_control_z[0] = Kd_z * (z_gap[0] - z_gap_old[0]) / dt;

	P_control_yaw[0] = Kp_yaw * yaw_gap[0];
	I_control_yaw[0] = I_control_yaw[0] + Ki_yaw * yaw_gap[0] * dt;
	D_control_yaw[0] = Kd_yaw * (yaw_gap[0] - yaw_gap_old[0]) / dt;

	x_speed_old[0] = x_speed[0];
	y_speed_old[0] = y_speed[0];
	z_gap_old[0] = z_gap[0];
	yaw_gap_old[0] = yaw_gap[0];

	double x_value = P_control_x[0] + I_control_x[0] + D_control_x[0];
	double y_value = P_control_y[0] + I_control_y[0] + D_control_y[0];
	double z_value = P_control_z[0] + I_control_z[0] + D_control_z[0];
	double yaw_value = P_control_yaw[0] + I_control_yaw[0] + D_control_yaw[0];

	// x is forward-backward (forward is positive), y is side (left is positive)
	if ( x_break ) ;
	else last_1.linear.x = x_value;
	if ( y_break ) ;
	else last_1.linear.y = y_value;
	last_1.linear.z = z_value;
	last_1.angular.z = yaw_value;

	pub_1[VELOCITY].publish(last_1);
}

void Control::position_control_2() {
	x_gap[1] = x_des[1] - x[1];
	y_gap[1] = y_des[1] - y[1];
	z_gap[1] = z_des[1] - z[1];

	if ( abs(yaw_des[1] - yaw[1]) <=  180) 	yaw_gap[1] = yaw_des[1] - yaw[1];
	else {
		if ( yaw_des[1] >= yaw[1]) yaw_gap[1] = -yaw[1] - (360 - yaw_des[1]);
		else yaw_gap[1] = yaw_des[1] + (360 - yaw[1]);
	}

	x_speed[1] = ( -sin(Deg2Rad(yaw[1])) * x_gap[1] + cos(Deg2Rad(yaw[1])) * y_gap[1] );
	y_speed[1] = ( -cos(Deg2Rad(yaw[1])) * x_gap[1] - sin(Deg2Rad(yaw[1])) * y_gap[1] );

	P_control_x[1] = Kp_x * x_speed[1];
	I_control_x[1] = I_control_x[1] + Ki_x * x_speed[1] * dt;
	D_control_x[1] = Kd_x * (x_speed[1] - x_speed_old[1]) / dt;

	P_control_y[1] = Kp_y * y_speed[1];
	I_control_y[1] = I_control_y[1] + Ki_y * y_speed[1] * dt;
	D_control_y[1] = Kd_y * (y_speed[1] - y_speed_old[1]) / dt;

	P_control_z[1] = Kp_z * z_gap[1];
	I_control_z[1] = I_control_z[1] + Ki_z * z_gap[1] * dt;
	D_control_z[1] = Kd_z * (z_gap[1] - z_gap_old[1]) / dt;

	P_control_yaw[1] = Kp_yaw * yaw_gap[1];
	I_control_yaw[1] = I_control_yaw[1] + Ki_yaw * yaw_gap[1] * dt;
	D_control_yaw[1] = Kd_yaw * (yaw_gap[1] - yaw_gap_old[1]) / dt;

	x_speed_old[1] = x_speed[1];
	y_speed_old[1] = y_speed[1];
	z_gap_old[1] = z_gap[1];
	yaw_gap_old[1] = yaw_gap[1];

	double x_value = P_control_x[1] + I_control_x[1] + D_control_x[1];
	double y_value = P_control_y[1] + I_control_y[1] + D_control_y[1];
	double z_value = P_control_z[1] + I_control_z[1] + D_control_z[1];
	double yaw_value = P_control_yaw[1] + I_control_yaw[1] + D_control_yaw[1];

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	if ( x_break ) ;
	else last_2.linear.x = x_value;
	if ( y_break ) ;
	else last_2.linear.y = y_value;
	last_2.linear.z = z_value;
	last_2.angular.z = yaw_value;

	pub_2[VELOCITY].publish(last_2);
}

void Control::position_control_3() {
	x_gap[2] = x_des[2] - x[2];
	y_gap[2] = y_des[2] - y[2];
	z_gap[2] = z_des[2] - z[2];

	if ( abs(yaw_des[2] - yaw[2]) <=  180) 	yaw_gap[2] = yaw_des[2] - yaw[2];
	else {
		if ( yaw_des[2] >= yaw[2]) yaw_gap[2] = -yaw[2] - (360 - yaw_des[2]);
		else yaw_gap[2] = yaw_des[2] + (360 - yaw[2]);
	}

	x_speed[2] = ( -sin(Deg2Rad(yaw[2])) * x_gap[2] + cos(Deg2Rad(yaw[2])) * y_gap[2] );
	y_speed[2] = ( -cos(Deg2Rad(yaw[2])) * x_gap[2] - sin(Deg2Rad(yaw[2])) * y_gap[2] );

	P_control_x[2] = Kp_x * x_speed[2];
	I_control_x[2] = I_control_x[2] + Ki_x * x_speed[2] * dt;
	D_control_x[2] = Kd_x * (x_speed[2] - x_speed_old[2]) / dt;

	P_control_y[2] = Kp_y * y_speed[2];
	I_control_y[2] = I_control_y[2] + Ki_y * y_speed[2] * dt;
	D_control_y[2] = Kd_y * (y_speed[2] - y_speed_old[2]) / dt;

	P_control_z[2] = Kp_z * z_gap[2];
	I_control_z[2] = I_control_z[2] + Ki_z * z_gap[2] * dt;
	D_control_z[2] = Kd_z * (z_gap[2] - z_gap_old[2]) / dt;

	P_control_yaw[2] = Kp_yaw * yaw_gap[2];
	I_control_yaw[2] = I_control_yaw[2] + Ki_yaw * yaw_gap[2] * dt;
	D_control_yaw[2] = Kd_yaw * (yaw_gap[2] - yaw_gap_old[2]) / dt;

	x_speed_old[2] = x_speed[2];
	y_speed_old[2] = y_speed[2];
	z_gap_old[2] = z_gap[2];
	yaw_gap_old[2] = yaw_gap[2];

	double x_value = P_control_x[2] + I_control_x[2] + D_control_x[2];
	double y_value = P_control_y[2] + I_control_y[2] + D_control_y[2];
	double z_value = P_control_z[2] + I_control_z[2] + D_control_z[2];
	double yaw_value = P_control_yaw[2] + I_control_yaw[2] + D_control_yaw[2];

	if ( x_break ) ;
	else last_3.linear.x = x_value;
	if ( y_break ) ;
	else last_3.linear.y = y_value;
	last_3.linear.z = z_value;
	last_3.angular.z = yaw_value;

	pub_3[VELOCITY].publish(last_3);
}

void Control::position_control_4() {
	x_gap[3] = x_des[3] - x[3];
	y_gap[3] = y_des[3] - y[3];
	z_gap[3] = z_des[3] - z[3];

	if ( abs(yaw_des[3] - yaw[3]) <=  180) 	yaw_gap[3] = yaw_des[3] - yaw[3];
	else {
		if ( yaw_des[3] >= yaw[3]) yaw_gap[3] = -yaw[3] - (360 - yaw_des[3]);
		else yaw_gap[3] = yaw_des[3] + (360 - yaw[3]);
	}

	x_speed[3] = ( -sin(Deg2Rad(yaw[3])) * x_gap[3] + cos(Deg2Rad(yaw[3])) * y_gap[3] );
	y_speed[3] = ( -cos(Deg2Rad(yaw[3])) * x_gap[3] - sin(Deg2Rad(yaw[3])) * y_gap[3] );

	P_control_x[3] = Kp_x * x_speed[3];
	I_control_x[3] = I_control_x[3] + Ki_x * x_speed[3] * dt;
	D_control_x[3] = Kd_x * (x_speed[3] - x_speed_old[3]) / dt;

	P_control_y[3] = Kp_y * y_speed[3];
	I_control_y[3] = I_control_y[3] + Ki_y * y_speed[3] * dt;
	D_control_y[3] = Kd_y * (y_speed[3] - y_speed_old[3]) / dt;

	P_control_z[3] = Kp_z * z_gap[3];
	I_control_z[3] = I_control_z[3] + Ki_z * z_gap[3] * dt;
	D_control_z[3] = Kd_z * (z_gap[3] - z_gap_old[3]) / dt;

	P_control_yaw[3] = Kp_yaw * yaw_gap[3];
	I_control_yaw[3] = I_control_yaw[3] + Ki_yaw * yaw_gap[3] * dt;
	D_control_yaw[3] = Kd_yaw * (yaw_gap[3] - yaw_gap_old[3]) / dt;

	x_speed_old[3] = x_speed[3];
	y_speed_old[3] = y_speed[3];
	z_gap_old[3] = z_gap[3];
	yaw_gap_old[3] = yaw_gap[3];

	double x_value = P_control_x[3] + I_control_x[3] + D_control_x[3];
	double y_value = P_control_y[3] + I_control_y[3] + D_control_y[3];
	double z_value = P_control_z[3] + I_control_z[3] + D_control_z[3];
	double yaw_value = P_control_yaw[3] + I_control_yaw[3] + D_control_yaw[3];

	if ( x_break ) ;
	else last_4.linear.x = x_value;
	if ( y_break ) ;
	else last_4.linear.y = y_value;
	last_4.linear.z = z_value;
	last_4.angular.z = yaw_value;

	pub_4[VELOCITY].publish(last_4);
}

void Control::position_control_5() {
	x_gap[4] = x_des[4] - x[4];
	y_gap[4] = y_des[4] - y[4];
	z_gap[4] = z_des[4] - z[4];

	if ( abs(yaw_des[4] - yaw[4]) <=  180) 	yaw_gap[4] = yaw_des[4] - yaw[4];
	else {
		if ( yaw_des[4] >= yaw[4]) yaw_gap[4] = -yaw[4] - (360 - yaw_des[4]);
		else yaw_gap[4] = yaw_des[4] + (360 - yaw[4]);
	}

	x_speed[4] = ( -sin(Deg2Rad(yaw[4])) * x_gap[4] + cos(Deg2Rad(yaw[4])) * y_gap[4] );
	y_speed[4] = ( -cos(Deg2Rad(yaw[4])) * x_gap[4] - sin(Deg2Rad(yaw[4])) * y_gap[4] );

	P_control_x[4] = Kp_x * x_speed[4];
	I_control_x[4] = I_control_x[4] + Ki_x * x_speed[4] * dt;
	D_control_x[4] = Kd_x * (x_speed[4] - x_speed_old[4]) / dt;

	P_control_y[4] = Kp_y * y_speed[4];
	I_control_y[4] = I_control_y[4] + Ki_y * y_speed[4] * dt;
	D_control_y[4] = Kd_y * (y_speed[4] - y_speed_old[4]) / dt;

	P_control_z[4] = Kp_z * z_gap[4];
	I_control_z[4] = I_control_z[4] + Ki_z * z_gap[4] * dt;
	D_control_z[4] = Kd_z * (z_gap[4] - z_gap_old[4]) / dt;

	P_control_yaw[4] = Kp_yaw * yaw_gap[4];
	I_control_yaw[4] = I_control_yaw[4] + Ki_yaw * yaw_gap[4] * dt;
	D_control_yaw[4] = Kd_yaw * (yaw_gap[4] - yaw_gap_old[4]) / dt;

	x_speed_old[4] = x_speed[4];
	y_speed_old[4] = y_speed[4];
	z_gap_old[4] = z_gap[4];
	yaw_gap_old[4] = yaw_gap[4];

	double x_value = P_control_x[4] + I_control_x[4] + D_control_x[4];
	double y_value = P_control_y[4] + I_control_y[4] + D_control_y[4];
	double z_value = P_control_z[4] + I_control_z[4] + D_control_z[4];
	double yaw_value = P_control_yaw[4] + I_control_yaw[4] + D_control_yaw[4];

	if ( x_break ) ;
	else last_5.linear.x = x_value;
	if ( y_break ) ;
	else last_5.linear.y = y_value;
	last_5.linear.z = z_value;
	last_5.angular.z = yaw_value;

	pub_5[VELOCITY].publish(last_5);
}

void Control::position_control_6() {
	x_gap[5] = x_des[5] - x[5];
	y_gap[5] = y_des[5] - y[5];
	z_gap[5] = z_des[5] - z[5];

	if ( abs(yaw_des[5] - yaw[5]) <=  180) 	yaw_gap[5] = yaw_des[5] - yaw[5];
	else {
		if ( yaw_des[5] >= yaw[5]) yaw_gap[5] = -yaw[5] - (360 - yaw_des[5]);
		else yaw_gap[5] = yaw_des[5] + (360 - yaw[5]);
	}

	x_speed[5] = ( -sin(Deg2Rad(yaw[5])) * x_gap[5] + cos(Deg2Rad(yaw[5])) * y_gap[5] );
	y_speed[5] = ( -cos(Deg2Rad(yaw[5])) * x_gap[5] - sin(Deg2Rad(yaw[5])) * y_gap[5] );

	P_control_x[5] = Kp_x * x_speed[5];
	I_control_x[5] = I_control_x[5] + Ki_x * x_speed[5] * dt;
	D_control_x[5] = Kd_x * (x_speed[5] - x_speed_old[5]) / dt;

	P_control_y[5] = Kp_y * y_speed[5];
	I_control_y[5] = I_control_y[5] + Ki_y * y_speed[5] * dt;
	D_control_y[5] = Kd_y * (y_speed[5] - y_speed_old[5]) / dt;

	P_control_z[5] = Kp_z * z_gap[5];
	I_control_z[5] = I_control_z[5] + Ki_z * z_gap[5] * dt;
	D_control_z[5] = Kd_z * (z_gap[5] - z_gap_old[5]) / dt;

	P_control_yaw[5] = Kp_yaw * yaw_gap[5];
	I_control_yaw[5] = I_control_yaw[5] + Ki_yaw * yaw_gap[5] * dt;
	D_control_yaw[5] = Kd_yaw * (yaw_gap[5] - yaw_gap_old[5]) / dt;

	x_speed_old[5] = x_speed[5];
	y_speed_old[5] = y_speed[5];
	z_gap_old[5] = z_gap[5];
	yaw_gap_old[5] = yaw_gap[5];

	double x_value = P_control_x[5] + I_control_x[5] + D_control_x[5];
	double y_value = P_control_y[5] + I_control_y[5] + D_control_y[5];
	double z_value = P_control_z[5] + I_control_z[5] + D_control_z[5];
	double yaw_value = P_control_yaw[5] + I_control_yaw[5] + D_control_yaw[5];

	if ( x_break ) ;
	else last_6.linear.x = x_value;
	if ( y_break ) ;
	else last_6.linear.y = y_value;
	last_6.linear.z = z_value;
	last_6.angular.z = yaw_value;

	pub_6[VELOCITY].publish(last_6);
}

void Control::position_control_7() {
	x_gap[6] = x_des[6] - x[6];
	y_gap[6] = y_des[6] - y[6];
	z_gap[6] = z_des[6] - z[6];

	if ( abs(yaw_des[6] - yaw[6]) <=  180) 	yaw_gap[6] = yaw_des[6] - yaw[6];
	else {
		if ( yaw_des[6] >= yaw[6]) yaw_gap[6] = -yaw[6] - (360 - yaw_des[6]);
		else yaw_gap[6] = yaw_des[6] + (360 - yaw[6]);
	}

	x_speed[6] = ( -sin(Deg2Rad(yaw[6])) * x_gap[6] + cos(Deg2Rad(yaw[6])) * y_gap[6] );
	y_speed[6] = ( -cos(Deg2Rad(yaw[6])) * x_gap[6] - sin(Deg2Rad(yaw[6])) * y_gap[6] );

	P_control_x[6] = Kp_x * x_speed[6];
	I_control_x[6] = I_control_x[6] + Ki_x * x_speed[6] * dt;
	D_control_x[6] = Kd_x * (x_speed[6] - x_speed_old[6]) / dt;

	P_control_y[6] = Kp_y * y_speed[6];
	I_control_y[6] = I_control_y[6] + Ki_y * y_speed[6] * dt;
	D_control_y[6] = Kd_y * (y_speed[6] - y_speed_old[6]) / dt;

	P_control_z[6] = Kp_z * z_gap[6];
	I_control_z[6] = I_control_z[6] + Ki_z * z_gap[6] * dt;
	D_control_z[6] = Kd_z * (z_gap[6] - z_gap_old[6]) / dt;

	P_control_yaw[6] = Kp_yaw * yaw_gap[6];
	I_control_yaw[6] = I_control_yaw[6] + Ki_yaw * yaw_gap[6] * dt;
	D_control_yaw[6] = Kd_yaw * (yaw_gap[6] - yaw_gap_old[6]) / dt;

	x_speed_old[6] = x_speed[6];
	y_speed_old[6] = y_speed[6];
	z_gap_old[6] = z_gap[6];
	yaw_gap_old[6] = yaw_gap[6];

	double x_value = P_control_x[6] + I_control_x[6] + D_control_x[6];
	double y_value = P_control_y[6] + I_control_y[6] + D_control_y[6];
	double z_value = P_control_z[6] + I_control_z[6] + D_control_z[6];
	double yaw_value = P_control_yaw[6] + I_control_yaw[6] + D_control_yaw[6];

	if ( x_break ) ;
	else last_7.linear.x = x_value;
	if ( y_break ) ;
	else last_7.linear.y = y_value;
	last_7.linear.z = z_value;
	last_7.angular.z = yaw_value;

	pub_7[VELOCITY].publish(last_7);
}

void Control::doMisc_1(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[0] = x[0];
				y_des[0] = y[0];
				z_des[0] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_1 = false;
			pub_1[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_1 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_1[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_1[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_1 = false;
		}
	}
}

void Control::doMisc_2(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[1] = x[1];
				y_des[1] = y[1];
				z_des[1] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_2 = false;
			pub_2[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_2 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_2[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_2[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_2 = false;
		}
	}
}

void Control::doMisc_3(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[2] = x[2];
				y_des[2] = y[2];
				z_des[2] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_3 = false;
			pub_3[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_3 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_3[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_3[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_3 = false;
		}
	}
}

void Control::doMisc_4(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[3] = x[3];
				y_des[3] = y[3];
				z_des[3] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_4 = false;
			pub_4[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_4 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_4[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_4[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_4 = false;
		}
	}
}

void Control::doMisc_5(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[4] = x[4];
				y_des[4] = y[4];
				z_des[4] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_5 = false;
			pub_5[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_5 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_5[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_5[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_5 = false;
		}
	}
}

void Control::doMisc_6(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[5] = x[5];
				y_des[5] = y[5];
				z_des[5] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_6 = false;
			pub_6[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_6 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_6[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_6[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_6 = false;
		}
	}
}

void Control::doMisc_7(short type) {
	if(type == DO_LAND) {
		bool position_setting = true;
		if ( takeoffNland_counter < 20 ) {
			if ( position_setting) {
				x_des[6] = x[6];
				y_des[6] = y[6];
				z_des[6] = 0.1;
				position_setting = false;
			}
		}
		else if ( takeoffNland_counter < 25 ) {
			std_msgs::Empty m;
			subscriber->manner_7 = false;
			pub_7[LAND].publish(m);
		}
		else {
			TakeoffNLandFlag = false;
			LandFlag_7 = false;
		}
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_7[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_7[TAKEOFF].publish(m);

		if ( takeoffNland_counter > 5)	{
			TakeoffNLandFlag = false;
			TakeoffFlag_7 = false;
		}
	}
}

void Control::doFlip_1(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_1[FLIP].publish(m);
}

void Control::doFlip_2(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_2[FLIP].publish(m);
}

void Control::doFlip_3(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_3[FLIP].publish(m);
}

void Control::doFlip_4(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_4[FLIP].publish(m);
}

void Control::doFlip_5(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_5[FLIP].publish(m);
}

void Control::doFlip_6(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_6[FLIP].publish(m);
}

void Control::doFlip_7(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_7[FLIP].publish(m);
}

void Control::LeftNRight_1() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_1.linear.y = 1;
			}
			else {
				last_1.linear.y = -1;
			}
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_1.linear.y = -1;
			}
			else {
				last_1.linear.y = 1;
			}
			pub_1[VELOCITY].publish(last_1);
		}
		else	{
			last_1.linear.y = 0;
			pub_1[VELOCITY].publish(last_1);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_1 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_1.linear.y = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_1.linear.y = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else	{
			last_1.linear.y = 0;
			pub_1[VELOCITY].publish(last_1);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_1 = false;
		}
	}
}

void Control::LeftNRight_2() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_2.linear.y = 1;
			}
			else {
				last_2.linear.y = -1;
			}
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_2.linear.y = -1;
			}
			else {
				last_2.linear.y = 1;
			}
			pub_2[VELOCITY].publish(last_2);
		}
		else	{
			last_2.linear.y = 0;
			pub_2[VELOCITY].publish(last_2);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_2 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_2.linear.y = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_2.linear.y = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else	{
			last_2.linear.y = 0;
			pub_2[VELOCITY].publish(last_2);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_2 = false;
		}
	}
}

void Control::LeftNRight_3() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_3.linear.y = 1;
			}
			else {
				last_3.linear.y = -1;
			}
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_3.linear.y = -1;
			}
			else {
				last_3.linear.y = 1;
			}
			pub_3[VELOCITY].publish(last_3);
		}
		else	{
			last_3.linear.y = 0;
			pub_3[VELOCITY].publish(last_3);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_3 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_3.linear.y = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_3.linear.y = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else	{
			last_3.linear.y = 0;
			pub_3[VELOCITY].publish(last_3);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_3 = false;
		}
	}
}

void Control::LeftNRight_4() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_4.linear.y = 1;
			}
			else {
				last_4.linear.y = -1;
			}
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_4.linear.y = -1;
			}
			else {
				last_4.linear.y = 1;
			}
			pub_4[VELOCITY].publish(last_4);
		}
		else	{
			last_4.linear.y = 0;
			pub_4[VELOCITY].publish(last_4);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_4 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_4.linear.y = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_4.linear.y = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else	{
			last_4.linear.y = 0;
			pub_4[VELOCITY].publish(last_4);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_4 = false;
		}
	}
}

void Control::LeftNRight_5() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_5.linear.y = 1;
			}
			else {
				last_5.linear.y = -1;
			}
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_5.linear.y = -1;
			}
			else {
				last_5.linear.y = 1;
			}
			pub_5[VELOCITY].publish(last_5);
		}
		else	{
			last_5.linear.y = 0;
			pub_5[VELOCITY].publish(last_5);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_5 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_5.linear.y = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_5.linear.y = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else	{
			last_5.linear.y = 0;
			pub_5[VELOCITY].publish(last_5);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_5 = false;
		}
	}
}

void Control::LeftNRight_6() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_6.linear.y = 1;
			}
			else {
				last_6.linear.y = -1;
			}
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_6.linear.y = -1;
			}
			else {
				last_6.linear.y = 1;
			}
			pub_6[VELOCITY].publish(last_6);
		}
		else	{
			last_6.linear.y = 0;
			pub_6[VELOCITY].publish(last_6);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_6 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_6.linear.y = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_6.linear.y = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else	{
			last_6.linear.y = 0;
			pub_6[VELOCITY].publish(last_6);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_6 = false;
		}
	}
}

void Control::LeftNRight_7() {
	y_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			if (direction) {
				last_7.linear.y = 1;
			}
			else {
				last_7.linear.y = -1;
			}
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 6)	{
			if (direction) {
				last_7.linear.y = -1;
			}
			else {
				last_7.linear.y = 1;
			}
			pub_7[VELOCITY].publish(last_7);
		}
		else	{
			last_7.linear.y = 0;
			pub_7[VELOCITY].publish(last_7);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_7 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_7.linear.y = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_7.linear.y = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else	{
			last_7.linear.y = 0;
			pub_7[VELOCITY].publish(last_7);
			y_break	= false;
			repeat = 0;
			MotionFlag = false;
			SideFlag_7 = false;
		}
	}
}

void Control::UpDown_1() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_1.linear.x = 1;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 6)	{
			last_1.linear.x = -1;
			pub_1[VELOCITY].publish(last_1);
		}
		else	{
			x_break	= false;
			last_1.linear.x = 0;
			repeat = 0;
			pub_1[VELOCITY].publish(last_1);
			MotionFlag = false;
			UpDownFlag_1 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_1.linear.x = -0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_1.linear.x = 0.5;
			pub_1[VELOCITY].publish(last_1);
		}
		else	{
			x_break	= false;
			last_1.linear.x = 0;
			repeat = 0;
			pub_1[VELOCITY].publish(last_1);
			MotionFlag = false;
			UpDownFlag_1 = false;
		}
	}
}

void Control::UpDown_2() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_2.linear.x = 1;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 6)	{
			last_2.linear.x = -1;
			pub_2[VELOCITY].publish(last_2);
		}
		else	{
			x_break	= false;
			last_2.linear.x = 0;
			repeat = 0;
			pub_2[VELOCITY].publish(last_2);
			MotionFlag = false;
			UpDownFlag_2 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_2.linear.x = -0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_2.linear.x = 0.5;
			pub_2[VELOCITY].publish(last_2);
		}
		else	{
			x_break	= false;
			last_2.linear.x = 0;
			repeat = 0;
			pub_2[VELOCITY].publish(last_2);
			MotionFlag = false;
			UpDownFlag_2 = false;
		}
	}
}

void Control::UpDown_3() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_3.linear.x = 1;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 6)	{
			last_3.linear.x = -1;
			pub_3[VELOCITY].publish(last_3);
		}
		else	{
			x_break	= false;
			last_3.linear.x = 0;
			repeat = 0;
			pub_3[VELOCITY].publish(last_3);
			MotionFlag = false;
			UpDownFlag_3 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_3.linear.x = -0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_3.linear.x = 0.5;
			pub_3[VELOCITY].publish(last_3);
		}
		else	{
			x_break	= false;
			last_3.linear.x = 0;
			repeat = 0;
			pub_3[VELOCITY].publish(last_3);
			MotionFlag = false;
			UpDownFlag_3 = false;
		}
	}
}

void Control::UpDown_4() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_4.linear.x = 1;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 6)	{
			last_4.linear.x = -1;
			pub_4[VELOCITY].publish(last_4);
		}
		else	{
			x_break	= false;
			last_4.linear.x = 0;
			repeat = 0;
			pub_4[VELOCITY].publish(last_4);
			MotionFlag = false;
			UpDownFlag_4 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_4.linear.x = -0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_4.linear.x = 0.5;
			pub_4[VELOCITY].publish(last_4);
		}
		else	{
			x_break	= false;
			last_4.linear.x = 0;
			repeat = 0;
			pub_4[VELOCITY].publish(last_4);
			MotionFlag = false;
			UpDownFlag_4 = false;
		}
	}
}

void Control::UpDown_5() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_5.linear.x = 1;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 6)	{
			last_5.linear.x = -1;
			pub_5[VELOCITY].publish(last_5);
		}
		else	{
			x_break	= false;
			last_5.linear.x = 0;
			repeat = 0;
			pub_5[VELOCITY].publish(last_5);
			MotionFlag = false;
			UpDownFlag_5 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_5.linear.x = -0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_5.linear.x = 0.5;
			pub_5[VELOCITY].publish(last_5);
		}
		else	{
			x_break	= false;
			last_5.linear.x = 0;
			repeat = 0;
			pub_5[VELOCITY].publish(last_5);
			MotionFlag = false;
			UpDownFlag_5 = false;
		}
	}
}

void Control::UpDown_6() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_6.linear.x = 1;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 6)	{
			last_6.linear.x = -1;
			pub_6[VELOCITY].publish(last_6);
		}
		else	{
			x_break	= false;
			last_6.linear.x = 0;
			repeat = 0;
			pub_6[VELOCITY].publish(last_6);
			MotionFlag = false;
			UpDownFlag_6 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_6.linear.x = -0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_6.linear.x = 0.5;
			pub_6[VELOCITY].publish(last_6);
		}
		else	{
			x_break	= false;
			last_6.linear.x = 0;
			repeat = 0;
			pub_6[VELOCITY].publish(last_6);
			MotionFlag = false;
			UpDownFlag_6 = false;
		}
	}
}

void Control::UpDown_7() {
	x_break	= true;
	if (repeat == 0) {
		if ( motion_counter < 3)	{
			last_7.linear.x = 1;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 6)	{
			last_7.linear.x = -1;
			pub_7[VELOCITY].publish(last_7);
		}
		else	{
			x_break	= false;
			last_7.linear.x = 0;
			repeat = 0;
			pub_7[VELOCITY].publish(last_7);
			MotionFlag = false;
			UpDownFlag_7 = false;
		}
	}
	else {
		if ( motion_counter < 4 && repeat >= 1)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 12 && repeat >= 1)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 16 && repeat >= 1)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 20 && repeat >= 2)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 28 && repeat >= 2)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 32 && repeat >= 2)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 36 && repeat >= 3)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 44 && repeat >= 3)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 48 && repeat >= 3)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 52 && repeat >= 4)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 60 && repeat >= 4)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 64 && repeat >= 4)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 68 && repeat >= 5)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 76 && repeat >= 5)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 80 && repeat >= 5)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 84 && repeat >= 6)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 92 && repeat >= 6)	{
			last_7.linear.x = -0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else if ( motion_counter < 96 && repeat >= 6)	{
			last_7.linear.x = 0.5;
			pub_7[VELOCITY].publish(last_7);
		}
		else	{
			x_break	= false;
			last_7.linear.x = 0;
			repeat = 0;
			pub_7[VELOCITY].publish(last_7);
			MotionFlag = false;
			UpDownFlag_7 = false;
		}
	}
}
