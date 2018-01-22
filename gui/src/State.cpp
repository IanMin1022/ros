#include "State.h"
#include <bebop_msgs/CommonCommonStateBatteryStateChanged.h>
#include <bebop_msgs/CommonCommonStateWifiSignalChanged.h>
#include <cmath>
#include <ros/ros.h>

State* stat;

State::State() {
}

State::~State() {
	destroy();
}

void State::destroy() {
	for(int i = 0; i < 7; i++) battery_sub[i].shutdown();
  for(int i = 0; i < 7; i++) wifi_sub[i].shutdown();
}

void State::subscribe(ros::NodeHandle& nh) {
	battery_sub[0] = nh.subscribe("/bebop_1/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_1, this);
  battery_sub[1] = nh.subscribe("/bebop_2/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_2, this);
  battery_sub[2] = nh.subscribe("/bebop_3/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_3, this);
  battery_sub[3] = nh.subscribe("/bebop_4/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_4, this);
  battery_sub[4] = nh.subscribe("/bebop_5/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_5, this);
  battery_sub[5] = nh.subscribe("/bebop_6/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_6, this);
  battery_sub[6] = nh.subscribe("/bebop_7/states/common/CommonState/BatteryStateChanged", 100, &State::setBattery_7, this);

	wifi_sub[0] = nh.subscribe("/bebop_1/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_1, this);
  wifi_sub[1] = nh.subscribe("/bebop_2/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_2, this);
  wifi_sub[2] = nh.subscribe("/bebop_3/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_3, this);
  wifi_sub[3] = nh.subscribe("/bebop_4/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_4, this);
  wifi_sub[4] = nh.subscribe("/bebop_5/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_5, this);
  wifi_sub[5] = nh.subscribe("/bebop_6/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_6, this);
  wifi_sub[6] = nh.subscribe("/bebop_7/states/common/CommonState/WifiSignalChanged", 100, &State::setWifi_7, this);
}

short State::getBattery_1() {
	return bat_1;
}

short State::getBattery_2() {
	return bat_2;
}

short State::getBattery_3() {
	return bat_3;
}

short State::getBattery_4() {
	return bat_4;
}

short State::getBattery_5() {
	return bat_5;
}

short State::getBattery_6() {
	return bat_6;
}

short State::getBattery_7() {
	return bat_7;
}

short State::getWifiStrength_1() {
	return wifi_1;
}

short State::getWifiStrength_2() {
	return wifi_2;
}

short State::getWifiStrength_3() {
	return wifi_3;
}

short State::getWifiStrength_4() {
	return wifi_4;
}

short State::getWifiStrength_5() {
	return wifi_5;
}

short State::getWifiStrength_6() {
	return wifi_6;
}

short State::getWifiStrength_7() {
	return wifi_7;
}

void State::setBattery_1(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_1 = battery->percent;
}

void State::setBattery_2(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_2 = battery->percent;
}

void State::setBattery_3(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_3 = battery->percent;
}

void State::setBattery_4(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_4 = battery->percent;
}

void State::setBattery_5(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_5 = battery->percent;
}

void State::setBattery_6(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_6 = battery->percent;
}

void State::setBattery_7(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr& battery) {
	bat_7 = battery->percent;
}

void State::setWifi_1(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_1 = wi->rssi;
}

void State::setWifi_2(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_2 = wi->rssi;
}

void State::setWifi_3(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_3 = wi->rssi;
}

void State::setWifi_4(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_4 = wi->rssi;
}

void State::setWifi_5(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_5 = wi->rssi;
}

void State::setWifi_6(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_6 = wi->rssi;
}

void State::setWifi_7(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr& wi) {
	wifi_7 = wi->rssi;
}
