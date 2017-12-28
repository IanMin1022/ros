#include "StateCheck.h"
#include <bebop_msgs/CommonCommonStateBatteryStateChanged.h>
#include <bebop_msgs/CommonCommonStateWifiSignalChanged.h>
#include <cmath>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>

StateCheck* stats;

StateCheck::StateCheck() {
	// ensure we start off with no fix
	pos.status.status = -1;
}

StateCheck::~StateCheck() {
	destroy();
}

void StateCheck::destroy() {
	for(int i = 0; i < 4; i++) sub[i].shutdown();
}

void StateCheck::subscribe(ros::NodeHandle& nh) {
	sub[0] = nh.subscribe("bebop_1/states/common/CommonState/BatteryStateChanged", 100, &StateCheck::setBattery, this);
	sub[1] = nh.subscribe("bebop_1/states/common/CommonState/WifiSignalChanged", 100, &StateCheck::setWifi, this);
	sub[2] = nh.subscribe("bebop_1/odom", 100, &StateCheck::setOdom, this);
	sub[3] = nh.subscribe("bebop_1/fix", 100, &StateCheck::setPos, this);

	// ROS_INFO("SUBSCRIBED");
}

short StateCheck::getBattery() {
	return bat;
}

short StateCheck::getWifiStrength() {
	return wifi;
}

double StateCheck::getXVelocity() {
	return odom.twist.twist.linear.x;
}

double StateCheck::getYVelocity() {
	return odom.twist.twist.linear.y;
}

double StateCheck::getZVelocity() {
	return odom.twist.twist.linear.z;
}

nav_msgs::Odometry* StateCheck::getOdom() {
	return &odom;
}

bool StateCheck::hasFix() {
	return pos.status.status != -1;
}

double StateCheck::getLatitude() {
	if( hasFix() ) return pos.latitude;
	else return nan("No Fix");
}

double StateCheck::getLongitude() {
	if( hasFix() ) return pos.longitude;
	else return nan("No Fix");
}

double StateCheck::getAltitude() {
	if( hasFix() ) return pos.altitude;
	else return nan("No Fix");
}

void StateCheck::setBattery(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat = battery->percent;

	// ROS_INFO("GOT BATT, %d", bat);
}

void StateCheck::setWifi(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi = wi->rssi;

	// ROS_INFO("GOT WIFI, %d", wifi);
}

void StateCheck::setOdom(const nav_msgs::OdometryConstPtr& od) {
	odom = *od;
}

void StateCheck::setPos(const sensor_msgs::NavSatFixConstPtr& po) {
	pos = *po;

	// ROS_INFO("GOT NAVFIX");
}
