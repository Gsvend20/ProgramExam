
//  *** Author: Group B264C  ***
//  *** Project: Miniproject***
//  *** Node: Approach node***
//  *** Created: 31-12-2015***
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;
// Creating Publisher and subscriber 
objectsros::Publisher velocity_publisher; //responsible for publishing the velocity data to the turtle1
ros::Subscriber customer_subscriber; //subscribes to the Pose message of the 'person' turtle
ros::Subscriber pose_subscriber; //subscribes to the Pose message of the 'robot' turtle
turtlesim::Pose turtlesim_pose;
turtlesim::Pose customer_pose;
double cordy;double cordx;void poseCallback(const turtlesim::Pose::ConstPtr & pose_message); // callback for own Posevoid custCallback(const turtlesim::Pose::ConstPtr & cust_message); // callback for customer Posevoid moveGoal(double m1, double m2, double distance_tolerance); // Make turtle move towards given goaldouble getDistance(double x1, double y1, double x2, double y2); // Get distance using pythagoras theoremint main(int argc, char **argv){ros::init(argc, argv, "customer_approacher");ros::NodeHandle n;velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);pose_subscriber = n.subscribe("/turtle1/pose", 10, poseCallback);customer_subscriber = n.subscribe("Miniproject/Customer", 10, custCallback);ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);// Seeding the random number generator with starting value using time at given secondsrand(time(0));ros::Rate rate(100);if (ros::ok()){
do{geometry_msgs::Twist msg;msg.linear.x = 2;msg.angular.z = 5 * double(rand()) / double(RAND_MAX) - 2; //sets a random angular velocityif (turtlesim_pose.x > 10 || turtlesim_pose.x <1 || turtlesim_pose.y >10 || turtlesim_pose.y < 1){ //boundaries of the cage the turtle can randomly walk inmsg.linear.x = 4;msg.angular.z = 10;} while (ros::ok());}}for (int sth = 23; ros::ok(); sth++){geometry_msgs::Twist msg;msg.linear.x = 2;msg.angular.z = 5 * double(rand()) / double(RAND_MAX) - 2; //sets a random angular velocityif (turtlesim_pose.x >10 || turtlesim_pose.x <1 || turtlesim_pose.y >10 || turtlesim_pose.y <1){ //boundariesof the cage the turtle can randomly walk inmsg.linear.x = 4;msg.angular.z = 10;}while(ros::ok()) {geometry_msgs::Twist msg;msg.linear.x = 2;msg.angular.z = 5*double(rand())/double(RAND_MAX)-2; //sets a random angular velocityif (turtlesim_pose.x >10 || turtlesim_pose.x <1 || turtlesim_pose.y >10 || turtlesim_pose.y <1){ //boundariesof the cage the turtle can randomly walk in       msg.linear.x =4;       msg.angular.z =10;}pub.publish(msg);rate.sleep();ros::spinOnce();}return 0;}void poseCallback(const turtlesim::Pose::ConstPtr & pose_message){
