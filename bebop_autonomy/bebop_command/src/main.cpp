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
  ROS_INFO("Fisrt node is executed");
  //Manual.transmit = do_it;
	control->key_1(do_it);
}

void Command_2(const std_msgs::String::ConstPtr& msg)
{
  const char* do_it = msg->data.c_str();
  ROS_INFO("Second node is executed");
	control->key_2(do_it);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "I'm the node master");
	ros::NodeHandle nh;
//	ros::NodeHandle local_nh("~");

//	local_nh.param( "font_path", Window::font_path, std::string("/usr/share/fonts/truetype/freefont/FreeSans.ttf") );
//	local_nh.param( "circle_path", Window::circle_path, std::string("/home/michionlion/catkin_ws/src/bebop_dobob/circle.bmp") );

	ros::Subscriber node_1 = nh.subscribe("Command_1", 100, Command_1);
	ros::Subscriber node_2 = nh.subscribe("Command_2", 100, Command_2);

//	bool fail = false;
//	input = new Input();
	stats = new StateTracker();
//	window = new Window(fail);
	control = new ManualControl();
//	patroller = new Patroller();

	control->advertise_1(nh);
  control->advertise_2(nh);

//	image_transport::ImageTransport it(nh);
//	image_transport::TransportHints hints("compressed", ros::TransportHints(), local_nh);
//	image_transport::Subscriber sub = it.subscribe("bebop/image_raw", 1, &Window::updateVideoTexture, window, hints);

	stats->subscribe(nh);

  ros::Rate loop_rate(1);

	// bool pressed;
	// InputWindow input(pressed);
	// if(pressed) {
	// ROS_ERROR("SDL INITIALIZER ERROR");
	// ros::shutdown();
	// return -1;
	// }


	// fprintf(stdout, "\nKeys:\nW: forward\tS: backward\nA: left\t\tD: right\nSPACE: up\tLSHIFT: down\nCTRL: land\tRSHIFT: takeoff\nUP: camera up\tDOWN: camera down\nLEFT: rot left\tRIGHT: rot right\nENTER: emergency rotor shutdown\n2: start video\t3: end video\n1: Take a camera snapshot\nUse I, J, K, and L sparingly for arial flips. You can also use '[' and ']' to start and stop autohome navigation.\nEnsure SDL Window is focused for input to be processed!\n");
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
//	delete window;
//	delete patroller;
	delete control;
	delete stats;
//delete input;
	return 0;
}
