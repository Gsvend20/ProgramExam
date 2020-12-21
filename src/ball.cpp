
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
#include <turtlesim/TeleportAbsolute.h>
#include <sstream>

//class creation
class ball{
private:
ros::NodeHandle n;

ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
ros::ServiceClient teleport_client = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
geometry_msgs::Twist move_msg;
turtlesim::TeleportAbsolute teleport_msg;

public:
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
void teleport(double posX, double posY, double angle){
    teleport_msg.request.x = posX;
    teleport_msg.request.y = posY;
    teleport_msg.request.theta = angle;
    teleport_client.call(teleport_msg);
}
void callbackMyPose(const turtlesim::Pose& pose) {
   my_pose = pose;
}
void respawn(){
    turtlesim::Kill kill_msg;
    kill_msg.request.name = "turtle1";
    kill_client.call(kill_msg);

    turtlesim::Spawn spawn_msg;
    spawn_msg.request.name = "turtle1";
    spawn_msg.request.x = 5.5;
    spawn_msg.request.y = 5.5;
    spawn_client.call(spawn_msg);

    turtlesim::SetPen pen_srv;
    pen_srv.request.off = true;
    pen_client.call(pen_srv);   
}
};
// Creating Publisher and subscriber 

//FUNCTION CALLS

//SUB CALLBACKS

int main(int argc, char *argv[]){
ros::init(argc,argv, "Ball");
ball asslugter;
ros::Rate loop_rate(10);

turtlesim::Kill kill_msg;
kill_msg.request.name = "turtle1";
asslugter.kill_client.call(kill_msg);

turtlesim::Spawn spawn_msg;
spawn_msg.request.name = "turtle1";
spawn_msg.request.x = 5.5;
spawn_msg.request.y = 5.5;
spawn_msg.request.theta = M_PI/2;
asslugter.spawn_client.call(spawn_msg);

turtlesim::SetPen pen_srv;
pen_srv.request.off = true;
asslugter.pen_client.call(pen_srv);

for (int i = 0; i < 10; i++)
{
    asslugter.move(1.0,0.0);
    loop_rate.sleep();
}

    while(ros::ok()){
        std::cout << "start pos \n" << asslugter.my_pose.theta;
        if(asslugter.my_pose.x > 10.9 || asslugter.my_pose.x < 0.1 &! asslugter.my_pose.x == 5.5){
            asslugter.respawn();
            ros::Duration(0.5).sleep(); //these are to fix potential bugs when a turtle is spawned in
        }

        if (asslugter.my_pose.y > 10.9 || asslugter.my_pose.y < 0.1 &! asslugter.my_pose.y == 0.0)
        {
            double targetAngle = M_PI*2 - asslugter.my_pose.theta;
            asslugter.teleport(asslugter.my_pose.x,asslugter.my_pose.y, targetAngle);
            std::cout << "start theta \n" << asslugter.my_pose.theta;
            //ros::Duration(0.5).sleep();//these are to fix potential bugs when a turtle is spawned in
        }
    
        asslugter.move(1.0,0.0);
        ros::spinOnce();
        }

    
    return 0;
}
