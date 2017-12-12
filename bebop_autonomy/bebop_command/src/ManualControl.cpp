#include "ManualControl.h"
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

#define SPEED_X_MAX 0.5
#define SPEED_Y_MAX 0.5
#define SPEED_Z_MAX 0.5
#define SPEED_YAW_MAX 0.5

#define Kp_x 0.4
#define Ki_x 0
#define Kd_x 0

#define Kp_y 0.4
#define Ki_y 0
#define Kd_y 0

#define Kp_z 0.4
#define Ki_z 0
#define Kd_z 0

#define Kp_yaw 0.02
#define Ki_yaw 0
#define Kd_yaw 0

#define dt 0.05

ManualControl* control;

void Motion_timer(const ros::TimerEvent& event) {
	if ( control->SideFlag ) {
		if ( control->SideFlag_1 ) {
			control->LeftNRight_1(control->side_counter);
		}

		if ( control->SideFlag_2 ) {
			control->LeftNRight_2(control->side_counter);
		}

		if ( control->SideFlag_3 ) {
			control->LeftNRight_3(control->side_counter);
		}

		if ( control->SideFlag_4 ) {
			control->LeftNRight_4(control->side_counter);
		}

		if ( control->SideFlag_5 ) {
			control->LeftNRight_5(control->side_counter);
		}

		if ( control->SideFlag_6 ) {
			control->LeftNRight_6(control->side_counter);
		}

		if ( control->SideFlag_7 ) {
			control->LeftNRight_7(control->side_counter);
		}

		control->side_counter++;
	}

	if ( control->UpDownFlag ) {
		if ( control->UpDownFlag_1 ) {
			control->UpDown_1(control->updown_counter);
		}

		if ( control->UpDownFlag_2 ) {
			control->UpDown_2(control->updown_counter);
		}

		if ( control->UpDownFlag_3 ) {
			control->UpDown_3(control->updown_counter);
		}

		if ( control->UpDownFlag_4 ) {
			control->UpDown_4(control->updown_counter);
		}

		if ( control->UpDownFlag_5 ) {
			control->UpDown_5(control->updown_counter);
		}

		if ( control->UpDownFlag_6 ) {
			control->UpDown_6(control->updown_counter);
		}

		if ( control->UpDownFlag_7 ) {
			control->UpDown_7(control->updown_counter);
		}

		control->updown_counter++;
	}
}

// 좌우, 앞뒤로 까딱 추가하기
int Converter(const char* input) {
	char flip_forward = 'F';
	char flip_backward = 'B';
	char flip_left = 'E';
	char flip_right = 'I';
	char land = 'L';
	char take_off = 'T';
	char side = 'S';
	char updown = 'P';
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
	else if (input[0] == land) {
		return 5;
	}
	else if (input[0] == take_off)	{
		return 6;
	}
	else if (input[0] == side)	{
		return 10;
	}
	else if (input[1] == updown)	{
		return 11;
	}
	else	{
		return 0;
	}
}

double Deg2Rad(double deg) {
	return deg * M_PI / 180;
}

void ManualControl::key_1(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_1(0);
			break;

		case 2:
			doFlip_1(1);
			break;

		case 3:
			doFlip_1(2);
			break;

		case 4:
			doFlip_1(3);
			break;

		case DO_LAND:
			doMisc_1(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_1(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_1 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_1 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_2(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_2(0);
			break;

		case 2:
			doFlip_2(1);
			break;

		case 3:
			doFlip_2(2);
			break;

		case 4:
			doFlip_2(3);
			break;

		case DO_LAND:
			doMisc_2(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_2(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_2 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_2 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_3(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_3(0);
			break;

		case 2:
			doFlip_3(1);
			break;

		case 3:
			doFlip_3(2);
			break;

		case 4:
			doFlip_3(3);
			break;

		case DO_LAND:
			doMisc_3(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_3(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_3 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_3 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_4(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_4(0);
			break;

		case 2:
			doFlip_4(1);
			break;

		case 3:
			doFlip_4(2);
			break;

		case 4:
			doFlip_4(3);
			break;

		case DO_LAND:
			doMisc_4(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_4(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_4 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_4 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_5(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_5(0);
			break;

		case 2:
			doFlip_5(1);
			break;

		case 3:
			doFlip_5(2);
			break;

		case 4:
			doFlip_5(3);
			break;

		case DO_LAND:
			doMisc_5(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_5(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_5 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_5 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_6(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_6(0);
			break;

		case 2:
			doFlip_6(1);
			break;

		case 3:
			doFlip_6(2);
			break;

		case 4:
			doFlip_6(3);
			break;

		case DO_LAND:
			doMisc_6(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_6(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_6 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_6 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::key_7(const char* transmit) {
	int flag = Converter(transmit);

	if(transmit != NULL)
		switch(flag) {
		case 1:
			doFlip_7(0);
			break;

		case 2:
			doFlip_7(1);
			break;

		case 3:
			doFlip_7(2);
			break;

		case 4:
			doFlip_7(3);
			break;

		case DO_LAND:
			doMisc_7(DO_LAND);
			break;

		case DO_TAKEOFF:
			doMisc_7(DO_TAKEOFF);
			break;

		case SIDE:
			control->SideFlag = true;
			control->SideFlag_7 = true;
			control->side_counter = 0;
			break;

		case UPDOWN:
			control->UpDownFlag = true;
			control->UpDownFlag_7 = true;
			control->updown_counter = 0;
			break;

		default:
			return;
		}
}

void ManualControl::advertise(ros::NodeHandle& nh) {
	pub_1[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_1/cmd_vel", 1);
	pub_1[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_1/takeoff", 1);
	pub_1[LAND] = nh.advertise<std_msgs::Empty>("bebop_1/land", 1);
	pub_1[RESET] = nh.advertise<std_msgs::Empty>("bebop_1/reset", 1);
	pub_1[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_1/camera_control", 1);
	pub_1[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_1/snapshot", 1);
	pub_1[RECORD] = nh.advertise<std_msgs::Bool>("bebop_1/record", 1);
	pub_1[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_1/flip", 1);
	pub_1[HOME] = nh.advertise<std_msgs::Bool>("bebop_1/autoflight/navigate_home", 1);

	pub_2[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_2/cmd_vel", 1);
	pub_2[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_2/takeoff", 1);
	pub_2[LAND] = nh.advertise<std_msgs::Empty>("bebop_2/land", 1);
	pub_2[RESET] = nh.advertise<std_msgs::Empty>("bebop_2/reset", 1);
	pub_2[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_2/camera_control", 1);
	pub_2[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_2/snapshot", 1);
	pub_2[RECORD] = nh.advertise<std_msgs::Bool>("bebop_2/record", 1);
	pub_2[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_2/flip", 1);
	pub_2[HOME] = nh.advertise<std_msgs::Bool>("bebop_2/autoflight/navigate_home", 1);

	pub_3[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_3/cmd_vel", 1);
	pub_3[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_3/takeoff", 1);
	pub_3[LAND] = nh.advertise<std_msgs::Empty>("bebop_3/land", 1);
	pub_3[RESET] = nh.advertise<std_msgs::Empty>("bebop_3/reset", 1);
	pub_3[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_3/camera_control", 1);
	pub_3[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_3/snapshot", 1);
	pub_3[RECORD] = nh.advertise<std_msgs::Bool>("bebop_3/record", 1);
	pub_3[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_3/flip", 1);
	pub_3[HOME] = nh.advertise<std_msgs::Bool>("bebop_3/autoflight/navigate_home", 1);

	pub_4[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_4/cmd_vel", 1);
	pub_4[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_4/takeoff", 1);
	pub_4[LAND] = nh.advertise<std_msgs::Empty>("bebop_4/land", 1);
	pub_4[RESET] = nh.advertise<std_msgs::Empty>("bebop_4/reset", 1);
	pub_4[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_4/camera_control", 1);
	pub_4[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_4/snapshot", 1);
	pub_4[RECORD] = nh.advertise<std_msgs::Bool>("bebop_4/record", 1);
	pub_4[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_4/flip", 1);
	pub_4[HOME] = nh.advertise<std_msgs::Bool>("bebop_4/autoflight/navigate_home", 1);

	pub_5[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_5/cmd_vel", 1);
	pub_5[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_5/takeoff", 1);
	pub_5[LAND] = nh.advertise<std_msgs::Empty>("bebop_5/land", 1);
	pub_5[RESET] = nh.advertise<std_msgs::Empty>("bebop_5/reset", 1);
	pub_5[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_5/camera_control", 1);
	pub_5[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_5/snapshot", 1);
	pub_5[RECORD] = nh.advertise<std_msgs::Bool>("bebop_5/record", 1);
	pub_5[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_5/flip", 1);
	pub_5[HOME] = nh.advertise<std_msgs::Bool>("bebop_5/autoflight/navigate_home", 1);

	pub_6[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_6/cmd_vel", 1);
	pub_6[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_6/takeoff", 1);
	pub_6[LAND] = nh.advertise<std_msgs::Empty>("bebop_6/land", 1);
	pub_6[RESET] = nh.advertise<std_msgs::Empty>("bebop_6/reset", 1);
	pub_6[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_6/camera_control", 1);
	pub_6[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_6/snapshot", 1);
	pub_6[RECORD] = nh.advertise<std_msgs::Bool>("bebop_6/record", 1);
	pub_6[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_6/flip", 1);
	pub_6[HOME] = nh.advertise<std_msgs::Bool>("bebop_6/autoflight/navigate_home", 1);

	pub_7[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_7/cmd_vel", 1);
	pub_7[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_7/takeoff", 1);
	pub_7[LAND] = nh.advertise<std_msgs::Empty>("bebop_7/land", 1);
	pub_7[RESET] = nh.advertise<std_msgs::Empty>("bebop_7/reset", 1);
	pub_7[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_7/camera_control", 1);
	pub_7[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_7/snapshot", 1);
	pub_7[RECORD] = nh.advertise<std_msgs::Bool>("bebop_7/record", 1);
	pub_7[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_7/flip", 1);
	pub_7[HOME] = nh.advertise<std_msgs::Bool>("bebop_7/autoflight/navigate_home", 1);
}
// horizontal axis is x, vertical axis is y.
void ManualControl::position_control_1() {
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

	double P_control_x = Kp_x * x_speed[0];
	double I_control_x = I_control_x + Ki_x * x_speed[0] * dt;
	double D_control_x = Kd_x * (x_speed[0] - x_speed_old[0]) / dt;

	double P_control_y = Kp_y * y_speed[0];
	double I_control_y = I_control_y + Ki_y * y_speed[0] * dt;
	double D_control_y = Kd_y * (y_speed[0] - y_speed_old[0]) / dt;

	double P_control_z = Kp_z * z_gap[0];
	double I_control_z = I_control_z + Ki_z * z_gap[0] * dt;
	double D_control_z = Kd_z * (z_gap[0] - z_gap_old[0]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[0];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[0] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[0] - yaw_gap_old[0]) / dt;

	x_speed_old[0] = x_speed[0];
	y_speed_old[0] = y_speed[0];
	z_gap_old[0] = z_gap[0];
	yaw_gap_old[0] = yaw_gap[0];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);
	//ROS_INFO("yaw  is %f", yaw_gap[0]);

	// x is forward-backward (forward is positive), y is side (left is positive)
	last.linear.x = x_value;
	last.linear.y = y_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_1[VELOCITY].publish(last);
}

void ManualControl::position_control_2() {
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

	double P_control_x = Kp_x * x_speed[1];
	double I_control_x = I_control_x + Ki_x * x_speed[1] * dt;
	double D_control_x = Kd_x * (x_speed[1] - x_speed_old[1]) / dt;

	double P_control_y = Kp_y * y_speed[1];
	double I_control_y = I_control_y + Ki_y * y_speed[1] * dt;
	double D_control_y = Kd_y * (y_speed[1] - y_speed_old[1]) / dt;

	double P_control_z = Kp_z * z_gap[1];
	double I_control_z = I_control_z + Ki_z * z_gap[1] * dt;
	double D_control_z = Kd_z * (z_gap[1] - z_gap_old[1]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[1];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[1] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[1] - yaw_gap_old[1]) / dt;

	x_speed_old[1] = x_speed[1];
	y_speed_old[1] = y_speed[1];
	z_gap_old[1] = z_gap[1];
	yaw_gap_old[1] = yaw_gap[1];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	ROS_INFO("yaw speed is %f", yaw_value);
	//ROS_INFO("yaw ***** is %f", yaw[1]);
	//ROS_INFO("yaw $$$$$$ is %f", yaw_des[1]);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_2[VELOCITY].publish(last);
}

void ManualControl::position_control_3() {
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

	double P_control_x = Kp_x * x_speed[2];
	double I_control_x = I_control_x + Ki_x * x_speed[2] * dt;
	double D_control_x = Kd_x * (x_speed[2] - x_speed_old[2]) / dt;

	double P_control_y = Kp_y * y_speed[2];
	double I_control_y = I_control_y + Ki_y * y_speed[2] * dt;
	double D_control_y = Kd_y * (y_speed[2] - y_speed_old[2]) / dt;

	double P_control_z = Kp_z * z_gap[2];
	double I_control_z = I_control_z + Ki_z * z_gap[2] * dt;
	double D_control_z = Kd_z * (z_gap[2] - z_gap_old[2]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[2];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[2] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[2] - yaw_gap_old[2]) / dt;

	x_speed_old[2] = x_speed[2];
	y_speed_old[2] = y_speed[2];
	z_gap_old[2] = z_gap[2];
	yaw_gap_old[2] = yaw_gap[2];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_3[VELOCITY].publish(last);
}

void ManualControl::position_control_4() {
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

	double P_control_x = Kp_x * x_speed[3];
	double I_control_x = I_control_x + Ki_x * x_speed[3] * dt;
	double D_control_x = Kd_x * (x_speed[3] - x_speed_old[3]) / dt;

	double P_control_y = Kp_y * y_speed[3];
	double I_control_y = I_control_y + Ki_y * y_speed[3] * dt;
	double D_control_y = Kd_y * (y_speed[3] - y_speed_old[3]) / dt;

	double P_control_z = Kp_z * z_gap[3];
	double I_control_z = I_control_z + Ki_z * z_gap[3] * dt;
	double D_control_z = Kd_z * (z_gap[3] - z_gap_old[3]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[3];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[3] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[3] - yaw_gap_old[3]) / dt;

	x_speed_old[3] = x_speed[3];
	y_speed_old[3] = y_speed[3];
	z_gap_old[3] = z_gap[3];
	yaw_gap_old[3] = yaw_gap[3];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_4[VELOCITY].publish(last);
}

void ManualControl::position_control_5() {
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

	double P_control_x = Kp_x * x_speed[4];
	double I_control_x = I_control_x + Ki_x * x_speed[4] * dt;
	double D_control_x = Kd_x * (x_speed[4] - x_speed_old[4]) / dt;

	double P_control_y = Kp_y * y_speed[4];
	double I_control_y = I_control_y + Ki_y * y_speed[4] * dt;
	double D_control_y = Kd_y * (y_speed[4] - y_speed_old[4]) / dt;

	double P_control_z = Kp_z * z_gap[4];
	double I_control_z = I_control_z + Ki_z * z_gap[4] * dt;
	double D_control_z = Kd_z * (z_gap[4] - z_gap_old[4]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[4];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[4] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[4] - yaw_gap_old[4]) / dt;

	x_speed_old[4] = x_speed[4];
	y_speed_old[4] = y_speed[4];
	z_gap_old[4] = z_gap[4];
	yaw_gap_old[4] = yaw_gap[4];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_5[VELOCITY].publish(last);
}

void ManualControl::position_control_6() {
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

	double P_control_x = Kp_x * x_speed[5];
	double I_control_x = I_control_x + Ki_x * x_speed[5] * dt;
	double D_control_x = Kd_x * (x_speed[5] - x_speed_old[5]) / dt;

	double P_control_y = Kp_y * y_speed[5];
	double I_control_y = I_control_y + Ki_y * y_speed[5] * dt;
	double D_control_y = Kd_y * (y_speed[5] - y_speed_old[5]) / dt;

	double P_control_z = Kp_z * z_gap[5];
	double I_control_z = I_control_z + Ki_z * z_gap[5] * dt;
	double D_control_z = Kd_z * (z_gap[5] - z_gap_old[5]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[5];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[5] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[5] - yaw_gap_old[5]) / dt;

	x_speed_old[5] = x_speed[5];
	y_speed_old[5] = y_speed[5];
	z_gap_old[5] = z_gap[5];
	yaw_gap_old[5] = yaw_gap[5];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_6[VELOCITY].publish(last);
}

void ManualControl::position_control_7() {
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

	double P_control_x = Kp_x * x_speed[6];
	double I_control_x = I_control_x + Ki_x * x_speed[6] * dt;
	double D_control_x = Kd_x * (x_speed[6] - x_speed_old[6]) / dt;

	double P_control_y = Kp_y * y_speed[6];
	double I_control_y = I_control_y + Ki_y * y_speed[6] * dt;
	double D_control_y = Kd_y * (y_speed[6] - y_speed_old[6]) / dt;

	double P_control_z = Kp_z * z_gap[6];
	double I_control_z = I_control_z + Ki_z * z_gap[6] * dt;
	double D_control_z = Kd_z * (z_gap[6] - z_gap_old[6]) / dt;

	double P_control_yaw = Kp_yaw * yaw_gap[6];
	double I_control_yaw = I_control_yaw + Ki_yaw * yaw_gap[6] * dt;
	double D_control_yaw = Kd_yaw * (yaw_gap[6] - yaw_gap_old[6]) / dt;

	x_speed_old[6] = x_speed[6];
	y_speed_old[6] = y_speed[6];
	z_gap_old[6] = z_gap[6];
	yaw_gap_old[6] = yaw_gap[6];

	double x_value = P_control_x + I_control_x + D_control_x;
	double y_value = P_control_y + I_control_y + D_control_y;
	double z_value = P_control_z + I_control_z + D_control_z;
	double yaw_value = P_control_yaw + I_control_yaw + D_control_yaw;

	if ( x_value > SPEED_X_MAX) x_value = SPEED_X_MAX;
	else if ( x_value < -SPEED_X_MAX) x_value = -SPEED_X_MAX;
	//ROS_INFO("x speed is %f", x_value);
	if ( y_value > SPEED_Y_MAX) y_value = SPEED_Y_MAX;
	else if ( y_value < -SPEED_Y_MAX) y_value = -SPEED_Y_MAX;
	//ROS_INFO("y speed is %f", y_value);
	if ( z_value > SPEED_Z_MAX) z_value = SPEED_Z_MAX;
	else if ( z_value < -SPEED_Z_MAX) z_value = -SPEED_Z_MAX;
	//ROS_INFO("z speed is %f", z_value);
	if ( yaw_value > SPEED_YAW_MAX) yaw_value = SPEED_YAW_MAX;
	else if ( yaw_value < -SPEED_YAW_MAX) yaw_value = -SPEED_YAW_MAX;
	//ROS_INFO("yaw speed is %f", yaw_value);

	// y is side, x is forward-backward (means they need to be switched when you save the value to publish)
	last.linear.x = x_value; // which acts like y_value;
	last.linear.y = y_value; // which acts like x_value;
	last.linear.z = z_value;
	last.angular.z = yaw_value;

	pub_7[VELOCITY].publish(last);
}

void ManualControl::doMisc_1(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_1 = false;
		pub_1[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_1[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_1[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_2(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_2 = false;
		pub_2[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_2[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_2[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_3(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_3 = false;
		pub_3[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_3[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_3[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_4(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_4 = false;
		pub_4[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_4[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_4[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_5(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_5 = false;
		pub_5[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_5[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_5[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_6(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_6 = false;
		pub_6[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_6[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_6[TAKEOFF].publish(m);
	}
}

void ManualControl::doMisc_7(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		subscriber->manner_7 = false;
		pub_7[LAND].publish(m);
	}
	else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_7[RESET].publish(m);
	}
	else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_7[TAKEOFF].publish(m);
	}
}

void ManualControl::doFlip_1(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_1[FLIP].publish(m);
}

void ManualControl::doFlip_2(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_2[FLIP].publish(m);
}

void ManualControl::doFlip_3(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_3[FLIP].publish(m);
}

void ManualControl::doFlip_4(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_4[FLIP].publish(m);
}

void ManualControl::doFlip_5(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_5[FLIP].publish(m);
}

void ManualControl::doFlip_6(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_6[FLIP].publish(m);
}

void ManualControl::doFlip_7(short type) {
	std_msgs::UInt8 m;
	m.data = type;
	pub_7[FLIP].publish(m);
}

void ManualControl::LeftNRight_1(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_1[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_1[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_1[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_1[VELOCITY].publish(motion);
		SideFlag_1 = false;
	}
}

void ManualControl::LeftNRight_2(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_2[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_2[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_2[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_2[VELOCITY].publish(motion);
		SideFlag_2 = false;
	}
}

void ManualControl::LeftNRight_3(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_3[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_3[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_3[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_3[VELOCITY].publish(motion);
		SideFlag_3 = false;
	}
}

void ManualControl::LeftNRight_4(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_4[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_4[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_4[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_4[VELOCITY].publish(motion);
		SideFlag_4 = false;
	}
}

void ManualControl::LeftNRight_5(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_5[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_5[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_5[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_5[VELOCITY].publish(motion);
		SideFlag_5 = false;
	}
}

void ManualControl::LeftNRight_6(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_6[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_6[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_6[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_6[VELOCITY].publish(motion);
		SideFlag_6 = false;
	}
}

void ManualControl::LeftNRight_7(short count) {
	if ( count == 0)	{
		motion.angular.z = 0;
		pub_7[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.angular.z = 0.1;
		pub_7[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.angular.z = -0.1;
		pub_7[VELOCITY].publish(motion);
	}
	else	{
		motion.angular.z = 0;
		pub_7[VELOCITY].publish(motion);
		SideFlag_7 = false;
	}
}

void ManualControl::UpDown_1(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_1[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_1[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_1[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_1[VELOCITY].publish(motion);
		UpDownFlag_1 = false;
	}
}

void ManualControl::UpDown_2(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_2[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_2[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_2[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_2[VELOCITY].publish(motion);
		UpDownFlag_2 = false;
	}
}

void ManualControl::UpDown_3(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_3[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_3[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_3[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_3[VELOCITY].publish(motion);
		UpDownFlag_3 = false;
	}
}

void ManualControl::UpDown_4(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_4[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_4[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_4[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_4[VELOCITY].publish(motion);
		UpDownFlag_4 = false;
	}
}

void ManualControl::UpDown_5(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_5[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_5[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_5[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_5[VELOCITY].publish(motion);
		UpDownFlag_5 = false;
	}
}

void ManualControl::UpDown_6(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_6[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_6[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_6[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_6[VELOCITY].publish(motion);
		UpDownFlag_6 = false;
	}
}

void ManualControl::UpDown_7(short count) {
	if ( count == 0)	{
		motion.linear.x = 0;
		pub_7[VELOCITY].publish(motion);
	}
	else if ( count == 1)	{
		motion.linear.x = 0.1;
		pub_7[VELOCITY].publish(motion);
	}
	else if ( count == 2)	{
		motion.linear.x = -0.1;
		pub_7[VELOCITY].publish(motion);
	}
	else	{
		motion.linear.x = 0;
		pub_7[VELOCITY].publish(motion);
		UpDownFlag_7 = false;
	}
}
