//BLIVER FLYTTETE OVER DW GUYS
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>



ros::NodeHandle n;

ros::Subscriber pose_sub = n.subscribe("/turtle1/pose",100, &ball::callbackMyPose, this);
ros::Subscriber pose_sub = n.subscribe("/turtle2/pose", 100);
ros::Subscriber pose_sub = n.subscribe("/turtle3/pose", 100);






int main(int argc, char *argv[]){

ros::init(argc,argv, "Dist");


}
