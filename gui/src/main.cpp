#include "Input.h"
#include "Window.h"
#include "State.h"
#include "GUI.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <stdio.h>
#include <string.h>
#include "std_msgs/String.h"

int main(int argc, char** argv) {
	ros::init(argc, argv, "GUI_node");
	ros::NodeHandle nh;
	ros::NodeHandle local_nh("~");

	local_nh.param( "font_path", Window::font_path, std::string("/home/ian/git/ros/src/gui/D2Coding.ttf") );

  bool fail = false;
	input = new Input();
  stat = new State();
	window = new Window(fail);

  window->subscribe(nh);
  stat->subscribe(nh);

	ros::Rate r(12);

  //system("terminator --new-tab -H --execute roslaunch vrpn_client_ros sample.launch server:=19.94.4.18 &");

	while( ros::ok() && window->ok() ) {
		ros::spinOnce();
		eventPoll();
		window->update();

		r.sleep();
	}

	ros::shutdown();
	delete window;
	delete input;
	delete stat;
	return 0;
}
