#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ManualControl.h"
#include "Script_subscriber.h"
#include <string>
#include <iostream>
#include <sstream>

Script_subscriber* subscriber;

Script_subscriber::Script_subscriber() {

}

Script_subscriber::~Script_subscriber() {

}

void Script_subscriber::subscribe(ros::NodeHandle& nh)
{
  sub[0] = nh.subscribe("Script_1", 100, &Script_subscriber::Script_node_1, this);
  sub[1] = nh.subscribe("Script_2", 100, &Script_subscriber::Script_node_2, this);
  sub[2] = nh.subscribe("Script_3", 100, &Script_subscriber::Script_node_3, this);
  sub[3] = nh.subscribe("Script_4", 100, &Script_subscriber::Script_node_4, this);
  sub[4] = nh.subscribe("Script_5", 100, &Script_subscriber::Script_node_5, this);
  sub[5] = nh.subscribe("Script_6", 100, &Script_subscriber::Script_node_6, this);
  sub[6] = nh.subscribe("Script_7", 100, &Script_subscriber::Script_node_7, this);
}

void Script_subscriber::Script_node_1(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_1(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_1 = true;
  	control -> x_des[0] = x;
    control -> y_des[0] = y;
    control -> z_des[0] = z;
    control -> yaw_des[0] = yaw;
  }
}

void Script_subscriber::Script_node_2(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_2(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_2 = true;
  	control -> x_des[1] = x;
    control -> y_des[1] = y;
    control -> z_des[1] = z;
    control -> yaw_des[1] = yaw;
  }
}

void Script_subscriber::Script_node_3(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_3(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_3 = true;
  	control -> x_des[2] = x;
    control -> y_des[2] = y;
    control -> z_des[2] = z;
    control -> yaw_des[2] = yaw;
  }
}

void Script_subscriber::Script_node_4(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_4(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_4 = true;
  	control -> x_des[3] = x;
    control -> y_des[3] = y;
    control -> z_des[3] = z;
    control -> yaw_des[3] = yaw;
  }
}

void Script_subscriber::Script_node_5(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_5(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_5 = true;
  	control -> x_des[4] = x;
    control -> y_des[4] = y;
    control -> z_des[4] = z;
    control -> yaw_des[4] = yaw;
  }
}

void Script_subscriber::Script_node_6(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_6(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_6 = true;
  	control -> x_des[5] = x;
    control -> y_des[5] = y;
    control -> z_des[5] = z;
    control -> yaw_des[5] = yaw;
  }
}

void Script_subscriber::Script_node_7(const std_msgs::String::ConstPtr& msg)
{
  const char* reading = msg->data.c_str();

  std::istringstream devide(reading);

  std::string temp;
  devide >> temp;
  double flag = ::atof(temp.c_str());

  if(flag == 0 && reading[0] != '0')
  {
    const char* do_it = msg->data.c_str();
    control-> key_7(do_it);
  }
  else
  {
    double x = ::atof(temp.c_str());

    devide >> temp;
    double y = ::atof(temp.c_str());

    devide >> temp;
    double z = ::atof(temp.c_str());

    devide >> temp;
    double yaw = ::atof(temp.c_str());

    // Check whether x_des moved well or not
    subscriber -> manner_7 = true;
  	control -> x_des[6] = x;
    control -> y_des[6] = y;
    control -> z_des[6] = z;
    control -> yaw_des[6] = yaw;
  }
}
