#include "ManualControl.h"
#include "Script_subscriber.h"
#include "StateTracker.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <stdio.h>
#include <string.h>

void Camera_node(const std_msgs::String::ConstPtr& msg) {
  // Splitting String in 4 sections and converting it to double
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double x_1 = ::atof(temp.c_str());

  devide >> temp;
  double y_1 = ::atof(temp.c_str());

  devide >> temp;
  double z_1 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_1 = ::atof(temp.c_str());

  devide >> temp;
  double x_2 = ::atof(temp.c_str());

  devide >> temp;
  double y_2 = ::atof(temp.c_str());

  devide >> temp;
  double z_2 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_2 = ::atof(temp.c_str());

  devide >> temp;
  double x_3 = ::atof(temp.c_str());

  devide >> temp;
  double y_3 = ::atof(temp.c_str());

  devide >> temp;
  double z_3 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_3 = ::atof(temp.c_str());

  devide >> temp;
  double x_4 = ::atof(temp.c_str());

  devide >> temp;
  double y_4 = ::atof(temp.c_str());

  devide >> temp;
  double z_4 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_4 = ::atof(temp.c_str());

  devide >> temp;
  double x_5 = ::atof(temp.c_str());

  devide >> temp;
  double y_5 = ::atof(temp.c_str());

  devide >> temp;
  double z_5 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_5 = ::atof(temp.c_str());

  devide >> temp;
  double x_6 = ::atof(temp.c_str());

  devide >> temp;
  double y_6 = ::atof(temp.c_str());

  devide >> temp;
  double z_6 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_6 = ::atof(temp.c_str());

  devide >> temp;
  double x_7 = ::atof(temp.c_str());

  devide >> temp;
  double y_7 = ::atof(temp.c_str());

  devide >> temp;
  double z_7 = ::atof(temp.c_str());

  devide >> temp;
  double yaw_7 = ::atof(temp.c_str());

  control -> x[0] = x_1;
  control -> y[0] = y_1;
  control -> z[0] = z_1;
  control -> yaw[0] = yaw_1;

  control -> x[1] = x_2;
  control -> y[1] = y_2;
  control -> z[1] = z_2;
  control -> yaw[1] = yaw_2;

  control -> x[2] = x_3;
  control -> y[2] = y_3;
  control -> z[2] = z_3;
  control -> yaw[2] = yaw_3;

  control -> x[3] = x_4;
  control -> y[3] = y_4;
  control -> z[3] = z_4;
  control -> yaw[3] = yaw_4;

  control -> x[4] = x_5;
  control -> y[4] = y_5;
  control -> z[4] = z_5;
  control -> yaw[4] = yaw_5;

  control -> x[5] = x_6;
  control -> y[5] = y_6;
  control -> z[5] = z_6;
  control -> yaw[5] = yaw_6;

  control -> x[6] = x_7;
  control -> y[6] = y_7;
  control -> z[6] = z_7;
  control -> yaw[6] = yaw_7;

  if ( subscriber->manner_1 )
    control->position_control_1();
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "node_master");
	ros::NodeHandle nh;
  //ros::NodeHandle local_nh("~");
  ros::Timer CheckTime = nh.createTimer(ros::Duration(0.3), Motion_timer);
	ros::Subscriber camera_node = nh.subscribe("Camera", 1000, Camera_node);

  // you should check the frequency and how it works depend on the frequency
  // need to add current coordinates subscriber (a.k.a camera node)

	stats = new StateTracker();
	control = new ManualControl();
  subscriber = new Script_subscriber();

	control->advertise(nh);

  subscriber->subscribe(nh);

	stats->subscribe(nh);

  ros::Rate loop_rate(100);

	while( ros::ok() ) {
		ros::spinOnce();

		// ROS_INFO( "STATS: Batt: %d%% Wifi: %d GPS: %s\nGPS: (Latitude: %0.6f Longitude: %0.6f)\nVELX: %0.3f VELY: %0.3f VELZ: %0.3f", stats->getBattery(), stats->getWifiStrength(), stats->hasFix() ? "Has Fix" : "No Fix", stats->getLatitude(), stats->getLongitude(), stats->getXVelocity(), stats->getYVelocity(), stats->getZVelocity() );
		loop_rate.sleep();
	}

	ros::shutdown();
  delete subscriber;
	delete control;
	delete stats;
	return 0;
}
