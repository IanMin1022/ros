#include "ManualControl.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <string>
#include <iostream>
#include <sstream>

#define Flip_forward 1
#define Flip_backword 2
#define FLip_left 3
#define FLip_right 4
#define DO_LAND 5
#define DO_TAKEOFF 6
#define DO_RESET 8

ManualControl* control;

// 좌우, 앞뒤로 까딱 추가하기
int Converter(const char* input)
{
	char flip_forward = 'F';
	char flip_backward = 'B';
	char flip_left = 'E';
	char flip_right = 'I';
	char land = 'L';
	char take_off = 'T';
	if (input[5] == flip_forward)
	{
		return 1;
	}
	else if (input[5] == flip_backward)
	{
		return 2;
	}
	else if (input[6] == flip_left)
	{
		return 3;
	}
	else if (input[6] == flip_right)
	{
		return 4;
	}
	else if (input[0] == land)
	{
		return 5;
	}
	else if (input[0] == take_off)
	{
		return 6;
	}
	else
	{
		return 0;
	}
}
/*
void ManualControl::test() {

	ROS_INFO("%lf", x_des[0]);
}
*/
void ManualControl::key_1(const char* transmit) {
	int flag = Converter(transmit);

	std::istringstream devide(transmit);

	// Splitting motion command and time
	std::string temp;
  devide >> temp;
	devide >> temp;

	double motion_timer = ::atof(temp.c_str());

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

		default:
			return;
		}
}


void ManualControl::advertise_1(ros::NodeHandle& nh) {
	pub_1[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_1/cmd_vel", 1);
	pub_1[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_1/takeoff", 1);
	pub_1[LAND] = nh.advertise<std_msgs::Empty>("bebop_1/land", 1);
	pub_1[RESET] = nh.advertise<std_msgs::Empty>("bebop_1/reset", 1);
	pub_1[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_1/camera_control", 1);
	pub_1[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_1/snapshot", 1);
	pub_1[RECORD] = nh.advertise<std_msgs::Bool>("bebop_1/record", 1);
	pub_1[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_1/flip", 1);
	pub_1[HOME] = nh.advertise<std_msgs::Bool>("bebop_1/autoflight/navigate_home", 1);
}

void ManualControl::advertise_2(ros::NodeHandle& nh) {
	pub_2[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_2/cmd_vel", 1);
	pub_2[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_2/takeoff", 1);
	pub_2[LAND] = nh.advertise<std_msgs::Empty>("bebop_2/land", 1);
	pub_2[RESET] = nh.advertise<std_msgs::Empty>("bebop_2/reset", 1);
	pub_2[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_2/camera_control", 1);
	pub_2[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_2/snapshot", 1);
	pub_2[RECORD] = nh.advertise<std_msgs::Bool>("bebop_2/record", 1);
	pub_2[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_2/flip", 1);
	pub_2[HOME] = nh.advertise<std_msgs::Bool>("bebop_2/autoflight/navigate_home", 1);
}

void ManualControl::position_control_1() {
	x_gap = x_des[0] - x[0];
	y_gap = y_des[0] - y[0];
	yaw_gap = yaw_des[0] - yaw[0];
	z_gap = z_des[0] - z[0];

	// 0 <= speed <= 1
	// change yaw to fit in 0 - 360

	// x_speed = ( sin(yaw) * x_gap - cos(yaw) * y_gap ) / ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90));
	// y_speed = ( cos(yaw - 90) * y_gap - sin(yaw - 90) * x_gap ) / ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90));
	// ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90)) = 1
	x_speed_old = x_speed;
	y_speed_old = y_speed;

	x_speed = ( sin(yaw[0]) * x_gap - cos(yaw[0]) * y_gap );
	y_speed = ( cos(yaw[0] - 90) * y_gap - sin(yaw[0] - 90) * x_gap );

	x_value = P_x_gain * x_gap + D_x_gain * (x_gap - x_gap_old) / dt;
	y_value = P_y_gain * y_gap + D_y_gain * (y_gap - y_gap_old) / dt;

	if ( x_value > 1) x_value = 1;
	else if ( x_value < -1) x_value = -1;

	if ( y_value > 1) x_value = 1;
	else if ( y_value < -1) x_value = -1;

	x_gap_old = x_gap;
	y_gap_old = y_gap;

	last.linear.x = x_value;
	last.linear.y = y_value;

	// give some offset
	if( z_des[0] > z[0] ) last.linear.z = speed;
	else if( z_des[0] < z[0] ) last.linear.z = -speed;
	else last.linear.z = 0;

	if( yaw_des[0] > yaw[0] ) last.angular.z = rotSpeed;
	else if( yaw_des[0] < yaw[0] ) last.angular.z = -rotSpeed;
	else last.angular.z = 0;


	pub_1[VELOCITY].publish(last);
}

void ManualControl::doMisc_1(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_1[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_1[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_1[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_2(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_2[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_2[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_2[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
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
