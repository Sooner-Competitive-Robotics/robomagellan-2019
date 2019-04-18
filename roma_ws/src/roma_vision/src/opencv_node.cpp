//Include ROS
#include <ros/ros.h>

//Include RoMa messages
#include "roma_msgs/motion_cmds.h"

//Publishers
ros::Publ

void traj_callback(roma_msgs::motion_cmds::ConstPtr& cmd)
{

}

int main(int argc, char **argv)
{
	//Initialize the OpenCV node
	ros::init(argc, argv, "opencv_node");

	//Set up the node handle for the node
	ros::NodeHandle opencv_node;

	//Subscribe to the trajectory commands being handed down
	ros::Subscriber traj_cmd_sub = opencv_node.subscribe(opencv_node.resolveName("/roma_trajectory/cmd"), 10, &traj_callback);

	//TODO: Subscribe to commands to turn on

	//TODO: Interface with the camera

	//Publish the (un)modified motion command to the obstacle avoidance node
	ros::S_Co
}