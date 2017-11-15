#include "ManualControl.h"
//#include "Patroller.h"
#include "StateTracker.h"
//#include "Window.h"
#include <geometry_msgs/Twist.h>
//#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <stdio.h>
#include <string.h>

ManualControl Manual;

void Command_1(const std_msgs::String::ConstPtr& msg)
{
  const char* do_it = msg->data.c_str();
  //ROS_INFO("Fisrt node is executed");
  //Manual.transmit = do_it;
	control->key_1(do_it);
}

void Command_2(const std_msgs::String::ConstPtr& msg)
{
  const char* do_it = msg->data.c_str();
  //ROS_INFO("Second node is executed");
	control->key_2(do_it);
}

void Script_node_1(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  int x_1 = ::atof(temp.c_str());

  devide >> temp;
  int y_1 = ::atof(temp.c_str());

  devide >> temp;
  int z_1 = ::atof(temp.c_str());

  devide >> temp;
  int yaw_1 = ::atof(temp.c_str());

  // Check whether x_des moved well or not
	control.x_des = x_1;
  control.y_des = y_1;
  control.z_des = z_1;
  control.yaw_des = yaw_1;
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "I'm the node master");
	ros::NodeHandle nh;
  //ros::NodeHandle local_nh("~");

	ros::Subscriber node_1 = nh.subscribe("Command_1", 100, Command_1);
	ros::Subscriber node_2 = nh.subscribe("Command_2", 100, Command_2);

  // you should check the frequency and how it works depend on the frequency
  ros::Subscriber script_node_1 = nh.subscribe("script_1", 100, Script_node_1);

  // need to add current coordinates subscriber (a.k.a camera node)

	stats = new StateTracker();
	control = new ManualControl();

	control->advertise_1(nh);
  control->advertise_2(nh);

	stats->subscribe(nh);

  ros::Rate loop_rate(1);

	while( ros::ok() ) {
		ros::spinOnce();
//	printf("am I working\n" );
//	eventPoll();
//	control->key();
		control->publishVel();
//	patroller->patrol();
//	control->publishCam();
//	window->update();

		// ROS_INFO( "STATS: Batt: %d%% Wifi: %d GPS: %s\nGPS: (Latitude: %0.6f Longitude: %0.6f)\nVELX: %0.3f VELY: %0.3f VELZ: %0.3f", stats->getBattery(), stats->getWifiStrength(), stats->hasFix() ? "Has Fix" : "No Fix", stats->getLatitude(), stats->getLongitude(), stats->getXVelocity(), stats->getYVelocity(), stats->getZVelocity() );
		loop_rate.sleep();
	}

	ros::shutdown();
	delete control;
	delete stats;
	return 0;
}
