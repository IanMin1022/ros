#include "ManualControl.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
//#include <stdio.h>

#define SPEED_INCREMENT 0.0125
#define ROTATE_INCREMENT 0.00625
#define Flip_forward 1
#define Flip_backword 2
#define FLip_left 3
#define FLip_right 4
#define DO_LAND 5
#define DO_TAKEOFF 6
#define DO_RESET 8

#define FIRST 101
#define SECOND 102
#define THIRD 103
#define FOURTH 104

ManualControl* control;
/*
ManualControl::ManualControl() {
	input->registerKeyListener(this);
}

ManualControl::~ManualControl() {
	input->unregisterKeyListener(this);
	for(auto & el : pub) {
		el.shutdown();
	}
	enabled = false;
}
*/
// 좌우, 앞뒤로 까딱 추가하기
int Converter(const char* input)
{
	char forward = 'f';
	char backward = 'b';
	char left = 'e';
	char right = 'i';
	char land = 'l';
	char take_off = 't';
	if (input[0] == forward)
	{
		return 1;
	}
	else if (input[0] == backward)
	{
		return 2;
	}
	else if (input[1] == left)
	{
		return 3;
	}
	else if (input[1] == right)
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

geometry_msgs::Twist* ManualControl::getLast() {
	return &last;
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

void ManualControl::publishVel() {
//	if(!enabled) return;
	double des_x = 0, des_y = 0, des_z = 0, des_yaw = 0;
	double x = 0, y = 0, z = 0, yaw = 0;
	int sector = 0;
	// 0 <= speed <= 1

	if (yaw >= 0 && yaw < 90) sector = 101;
	else if (yaw >= 90 && yaw <= 180) sector = 102;
	else if (yaw >= -180 && yaw < -90) sector = 103;
	else if (yaw >= -90 && yaw < 0) sector = 104;

	switch (sector) {
		case FIRST:
					if( des_x > x ) last.linear.x = (yaw / 90 *speed) + ((90-yaw) / yaw * speed);
					else if( des_x < x ) last.linear.x = -((yaw / 90 *speed) + ((90-yaw) / yaw * speed));
					else last.linear.x = 0;

					if( input->isKeyDown(SDL_SCANCODE_A) && !input->isKeyDown(SDL_SCANCODE_D) ) last.linear.y = speed;
					else if( !input->isKeyDown(SDL_SCANCODE_A) && input->isKeyDown(SDL_SCANCODE_D) ) last.linear.y = -speed;
					break;
		case SECOND:
					break;
		case THIRD:
					break;
		case FOURTH:
					break;
		default:
					return;
	}

	if( des_z > z ) last.linear.z = speed;
	else if( des_z < z ) last.linear.z = -speed;
	else last.linear.z = 0;

	if( des_yaw > yaw ) last.angular.z = rotSpeed;
	else if( des_yaw < yaw ) last.angular.z = -rotSpeed;
	else last.angular.z = 0;


	pub[VELOCITY].publish(last);
}

void ManualControl::doMisc_1(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_1[LAND].publish(m);
		ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_1[RESET].publish(m);
		ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_1[TAKEOFF].publish(m);
		ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_2(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_2[LAND].publish(m);
		ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_2[RESET].publish(m);
		ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_2[TAKEOFF].publish(m);
		ROS_INFO("EXECUTING TAKEOFF!!");
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
