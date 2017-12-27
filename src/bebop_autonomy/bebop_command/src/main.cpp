#include "Control.h"
#include "Script_subscriber.h"
#include "StateCheck.h"
#include "Camera.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	ros::init(argc, argv, "node_master");
	ros::NodeHandle nh;
  //ros::NodeHandle local_nh("~");
  ros::Timer CheckTime = nh.createTimer(ros::Duration(0.05), Motion_timer);
	//ros::Subscriber camera_node = nh.subscribe("Camera", 1000, Camera_node);

  // you should check the frequency and how it works depend on the frequency
  // need to add current coordinates subscriber (a.k.a camera node)

	stats = new StateCheck();
	control = new Control();
  subscriber = new Script_subscriber();
  camera_node = new Camera_node();

	control->advertise(nh);

  subscriber->subscribe(nh);
  camera_node->subscribe(nh);
	stats->subscribe(nh);

  ros::Rate loop_rate(100);

	while( ros::ok() ) {
		ros::spinOnce();
    //ROS_INFO("x = %f", control->x[0]);
    //ROS_INFO("y = %f", control->y[0]);
    //ROS_INFO("z = %f", control->z[0]);
    //ROS_INFO("yaw = %f", control->yaw[0]);
		// ROS_INFO( "STATS: Batt: %d%% Wifi: %d GPS: %s\nGPS: (Latitude: %0.6f Longitude: %0.6f)\nVELX: %0.3f VELY: %0.3f VELZ: %0.3f", stats->getBattery(), stats->getWifiStrength(), stats->hasFix() ? "Has Fix" : "No Fix", stats->getLatitude(), stats->getLongitude(), stats->getXVelocity(), stats->getYVelocity(), stats->getZVelocity() );
		loop_rate.sleep();
	}

	ros::shutdown();
  delete camera_node;
  delete subscriber;
	delete control;
	delete stats;
	return 0;
}
