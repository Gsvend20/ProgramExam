
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>  
#include <turtlesim/SetPen.h>
#include <sstream>

//class creation
class ball{
private:
ros::NodeHandle n;


ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
geometry_msgs::Twist move_msg;

public:
//ros::Subscriber pose_sub = n.subscribe<turtlesim::Pose>("/ball/pose", 1, &ball::callbackMyPose, this);
ros::ServiceClient spawn_client = n.serviceClient<turtlesim::Spawn>("/spawn");
ros::ServiceClient kill_client = n.serviceClient<turtlesim::Kill>("/kill");
ros::ServiceClient pen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
ros::Subscriber pose_sub = n.subscribe("/turtle1/pose",100, &ball::callbackMyPose, this);
turtlesim::Pose my_pose;

void move(double xSpeed, double turnSpeed){
    move_msg.linear.x = xSpeed;
    move_msg.angular.z = turnSpeed;
    vel_pub.publish(move_msg); 
}
void callbackMyPose(const turtlesim::Pose& pose) {
   my_pose = pose;
}
};
// Creating Publisher and subscriber 

//FUNCTION CALLS


//SUB CALLBACKS




int main(int argc, char *argv[]){
ros::init(argc,argv, "Ball");
ball balled;
ros::Rate loop_rate(1);
turtlesim::Kill kill_msg;
kill_msg.request.name = "turtle1";
balled.kill_client.call(kill_msg);

turtlesim::Spawn spawn_msg;
spawn_msg.request.name = "turtle1";
spawn_msg.request.x = 5.5;
spawn_msg.request.y = 5.5;
balled.spawn_client.call(spawn_msg);

turtlesim::SetPen pen_srv;
pen_srv.request.off = true;
balled.pen_client.call(pen_srv);

    while(ros::ok()){
        if(balled.my_pose.x > 10.9 || balled.my_pose.x < 0.1){
            turtlesim::Kill kill_msg;
            kill_msg.request.name = "turtle1";
            balled.kill_client.call(kill_msg);

            turtlesim::Spawn spawn_msg;
            spawn_msg.request.name = "turtle1";
            spawn_msg.request.x = 5.5;
            spawn_msg.request.y = 5.5;
            balled.spawn_client.call(spawn_msg);

            turtlesim::SetPen pen_srv;
            pen_srv.request.off = true;
            balled.pen_client.call(pen_srv);    
            ros::Duration(0.5).sleep();
        }
  /*   for (int i = 0; i < M_PI/2*10; i++)
            {
                 balled.move(0.0,100);
                 loop_rate.sleep();
            }
            for (int i = 0; i < 50; i++)
            {
                 balled.move(1.0,0.0);
                 loop_rate.sleep();
            }*/
        balled.move(1.0,0);
        ros::spinOnce();
        }

    
    return 0;
}
