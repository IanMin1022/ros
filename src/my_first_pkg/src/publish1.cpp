#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker1");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter1", 1);

  ros::Rate loop_rate(1);

  int count = 0;
  if (ros::ok())
  {
    std_msgs::String msg;

    //chatter_pub.publish(msg);

    loop_rate.sleep();

    while (count <5) {

      if (count < 1) {
        std::stringstream ss;
        ss << "Let's start ";
        msg.data = ss.str();
      }
      else if (count < 2) {
        std::stringstream ss;
        ss << "I am a hero ";
        msg.data = ss.str();
      }      else if (count < 3) {
        std::stringstream ss;
        ss << "Actually I am batman ";
        msg.data = ss.str();
      }
      else if (count < 4) {
        std::stringstream ss;
        ss << "I love batcar ";
        msg.data = ss.str();
      }
      else if (count < 5) {
        std::stringstream ss;
        ss << "Time to end";
        msg.data = ss.str();
      }

      ROS_INFO("%s", msg.data.c_str());

      chatter_pub.publish(msg);

      ros::spinOnce();

      loop_rate.sleep();
      ++count;
    }

  }


  return 0;
}
