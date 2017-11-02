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
	/*
	ManualControl(void);
	~ManualControl(void);
	void toggle(void);
	bool isEnabled(void);
	*/
	void publishVel(void);
	void doMisc_1(short);
	void doMisc_2(short);
	void doFlip_1(short);
	void doFlip_2(short);
	void advertise_1(ros::NodeHandle&);
	void advertise_2(ros::NodeHandle&);
	void key_1(const char* transmit);
	void key_2(const char* transmit);
	geometry_msgs::Twist* getLast(void);


private:
	bool enabled = true;
	ros::Publisher pub_1[9];
	ros::Publisher pub_2[9];
	double speed = 0.7;
	double rotSpeed = 0.7;
	double camX = 0;
	double camY = 0;
	geometry_msgs::Twist last;
};

extern ManualControl* control;

#endif
