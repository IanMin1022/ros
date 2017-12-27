#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"

void camera_check(const geometry_msgs::PoseStamped& msgPose)
{
    //typeRNum posetypeRNum [5]={0,0,0,0,0};
    //tool.getPose(msgPose, posetypeRNum);

    ROS_INFO("fisrt: [%f]", msgPose.pose.position.x);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "not_listening");
  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("/vrpn_client_node/Drone01/pose", 1000, camera_check);

  ros::Rate loop_rate(100);

  while( ros::ok() ) {
		ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
