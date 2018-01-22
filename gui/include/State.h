#ifndef __STATE_H__
#define __STATE_H__

#include <bebop_msgs/CommonCommonStateBatteryStateChanged.h>
#include <bebop_msgs/CommonCommonStateWifiSignalChanged.h>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>

class State {
public:
	State(void);
	~State(void);
	void destroy(void);

	short getBattery_1(void);
  short getBattery_2(void);
  short getBattery_3(void);
  short getBattery_4(void);
  short getBattery_5(void);
  short getBattery_6(void);
  short getBattery_7(void);
	short getWifiStrength_1(void);
  short getWifiStrength_2(void);
  short getWifiStrength_3(void);
  short getWifiStrength_4(void);
  short getWifiStrength_5(void);
  short getWifiStrength_6(void);
  short getWifiStrength_7(void);

	nav_msgs::Odometry* getOdom(void);

	void setBattery_1(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_2(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_3(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_4(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_5(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_6(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
  void setBattery_7(const bebop_msgs::CommonCommonStateBatteryStateChangedConstPtr&);
	void setWifi_1(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_2(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_3(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_4(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_5(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_6(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);
  void setWifi_7(const bebop_msgs::CommonCommonStateWifiSignalChangedConstPtr&);

	void subscribe(ros::NodeHandle&);

private:
	short bat_1 = 95, bat_2 = 95, bat_3 = 95, bat_4 = 95, bat_5 = 95, bat_6 = 95, bat_7 = 95;
	short wifi_1 = 100, wifi_2 = 100, wifi_3 = 100, wifi_4 = 100, wifi_5 = 100, wifi_6 = 100, wifi_7 = 100;
	ros::Subscriber battery_sub[7];
  ros::Subscriber wifi_sub[7];
};

extern State* stat;

#endif
