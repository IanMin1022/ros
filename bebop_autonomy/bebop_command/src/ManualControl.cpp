#include "ManualControl.h"
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

double Deg2Pi(double deg)
{
	return deg * M_PI / 180;
}

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
			ROS_INFO("I'm landing");
			break;

		case DO_TAKEOFF:
			doMisc_1(DO_TAKEOFF);
			ROS_INFO("I'm taking off");
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

void ManualControl::advertise_3(ros::NodeHandle& nh) {
	pub_3[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_3/cmd_vel", 1);
	pub_3[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_3/takeoff", 1);
	pub_3[LAND] = nh.advertise<std_msgs::Empty>("bebop_3/land", 1);
	pub_3[RESET] = nh.advertise<std_msgs::Empty>("bebop_3/reset", 1);
	pub_3[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_3/camera_control", 1);
	pub_3[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_3/snapshot", 1);
	pub_3[RECORD] = nh.advertise<std_msgs::Bool>("bebop_3/record", 1);
	pub_3[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_3/flip", 1);
	pub_3[HOME] = nh.advertise<std_msgs::Bool>("bebop_3/autoflight/navigate_home", 1);
}

void ManualControl::advertise_4(ros::NodeHandle& nh) {
	pub_4[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_4/cmd_vel", 1);
	pub_4[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_4/takeoff", 1);
	pub_4[LAND] = nh.advertise<std_msgs::Empty>("bebop_4/land", 1);
	pub_4[RESET] = nh.advertise<std_msgs::Empty>("bebop_4/reset", 1);
	pub_4[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_4/camera_control", 1);
	pub_4[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_4/snapshot", 1);
	pub_4[RECORD] = nh.advertise<std_msgs::Bool>("bebop_4/record", 1);
	pub_4[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_4/flip", 1);
	pub_4[HOME] = nh.advertise<std_msgs::Bool>("bebop_4/autoflight/navigate_home", 1);
}

void ManualControl::advertise_5(ros::NodeHandle& nh) {
	pub_5[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_5/cmd_vel", 1);
	pub_5[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_5/takeoff", 1);
	pub_5[LAND] = nh.advertise<std_msgs::Empty>("bebop_5/land", 1);
	pub_5[RESET] = nh.advertise<std_msgs::Empty>("bebop_5/reset", 1);
	pub_5[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_5/camera_control", 1);
	pub_5[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_5/snapshot", 1);
	pub_5[RECORD] = nh.advertise<std_msgs::Bool>("bebop_5/record", 1);
	pub_5[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_5/flip", 1);
	pub_5[HOME] = nh.advertise<std_msgs::Bool>("bebop_5/autoflight/navigate_home", 1);
}

void ManualControl::advertise_6(ros::NodeHandle& nh) {
	pub_6[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_6/cmd_vel", 1);
	pub_6[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_6/takeoff", 1);
	pub_6[LAND] = nh.advertise<std_msgs::Empty>("bebop_6/land", 1);
	pub_6[RESET] = nh.advertise<std_msgs::Empty>("bebop_6/reset", 1);
	pub_6[CAMERA] = nh.advertise<geometry_msgs::Twist>("bebop_6/camera_control", 1);
	pub_6[SNAPSHOT] = nh.advertise<std_msgs::Empty>("bebop_6/snapshot", 1);
	pub_6[RECORD] = nh.advertise<std_msgs::Bool>("bebop_6/record", 1);
	pub_6[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_6/flip", 1);
	pub_6[HOME] = nh.advertise<std_msgs::Bool>("bebop_6/autoflight/navigate_home", 1);
}

void ManualControl::advertise_7(ros::NodeHandle& nh) {
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

void ManualControl::position_control_1() {
	x_gap[0] = x_des[0] - x[0];
	y_gap[0] = y_des[0] - y[0];
	z_gap[0] = z_des[0] - z[0];
	yaw_gap[0] = yaw_des[0] - yaw[0];

	// 0 <= speed <= 1
	// change yaw to fit in 0 - 360
	// x_speed = ( sin(yaw) * x_gap - cos(yaw) * y_gap ) / ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90));
	// y_speed = ( cos(yaw - 90) * y_gap - sin(yaw - 90) * x_gap ) / ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90));
	// ( sin(yaw) * cos(yaw - 90) - cos(yaw) * sin(yaw - 90)) = 1

	x_speed[0] = ( sin(Deg2Pi(yaw[0] + 90)) * x_gap[0] - cos(Deg2Pi(yaw[0] + 90)) * y_gap[0] );
	y_speed[0] = ( cos(Deg2Pi(yaw[0])) * y_gap[0] - sin(Deg2Pi(yaw[0])) * x_gap[0] );

	x_value = P_x_gain * x_speed[0] + D_x_gain * (x_speed[0] - x_speed_old[0]) / dt;
	y_value = P_y_gain * y_speed[0] + D_y_gain * (y_speed[0] - y_speed_old[0]) / dt;

	if ( x_value > 1) x_value = 1;
	else if ( x_value < -1) x_value = -1;
	ROS_INFO(" x value :::::: %f ", x_value);
	if ( y_value > 1) y_value = 1;
	else if ( y_value < -1) y_value = -1;
	ROS_INFO(" y value :::::: %f ", y_value);

	x_speed_old[0] = x_speed[0];
	y_speed_old[0] = y_speed[0];

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

void ManualControl::doMisc_3(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_3[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_3[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_3[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_4(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_4[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_4[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_4[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_5(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_5[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_5[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_5[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_6(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_6[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_6[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_6[TAKEOFF].publish(m);
		//ROS_INFO("EXECUTING TAKEOFF!!");
	}
}

void ManualControl::doMisc_7(short type) {
	if(type == DO_LAND) {
		std_msgs::Empty m;
		pub_7[LAND].publish(m);
		//ROS_INFO("EXECUTING LAND!!");
	} else if(type == DO_RESET) {
		std_msgs::Empty m;
		pub_7[RESET].publish(m);
		//ROS_INFO("EXECUTING EMERGENCY ROTOR STOP!!");
	} else if(type == DO_TAKEOFF) {
		std_msgs::Empty m;
		pub_7[TAKEOFF].publish(m);
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
