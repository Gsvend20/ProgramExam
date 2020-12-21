
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
    int randomAngle = rand() % 360 + 1;
    ROS_INFO("Random angle: %d", randomAngle);
    double header = randomAngle*M_PI/180;
    spawn_msg.request.theta = header;
    spawn_client.call(spawn_msg);

    turtlesim::SetPen pen_srv;
    pen_srv.request.off = true;
    pen_client.call(pen_srv);   
}
};

int main(int argc, char *argv[]){
ros::init(argc,argv, "Ball");
ball moving_balls;
srand (time(NULL));
ros::Rate loop_rate(10);
double speed = 1.0;

turtlesim::Kill kill_msg;
kill_msg.request.name = "turtle1";
moving_balls.kill_client.call(kill_msg);


int randomAngle = rand() % 360 + 1;
ROS_INFO("Random angle: %d", randomAngle);
double header = randomAngle*M_PI/180;

turtlesim::Spawn spawn_msg;
spawn_msg.request.name = "turtle1";
spawn_msg.request.x = 5.5;
spawn_msg.request.y = 5.5;
spawn_msg.request.theta = header;
moving_balls.spawn_client.call(spawn_msg);

turtlesim::SetPen pen_srv;
pen_srv.request.off = true;
moving_balls.pen_client.call(pen_srv);

for (int i = 0; i < 10; i++)
{
    moving_balls.move(1.0,0.0);
    loop_rate.sleep();
}

    while(ros::ok()){
        if(moving_balls.my_pose.x > 10.9 || moving_balls.my_pose.x < 0.2){
            moving_balls.respawn();
            ros::Duration(1.0).sleep(); //these are to fix potential bugs when a turtle is spawned 
            double speed = 1.0;
        }

        if (moving_balls.my_pose.y > 10.9 || moving_balls.my_pose.y < 0.1 &! moving_balls.my_pose.y == 0.0)
        {
            double targetAngle = M_PI*2 - moving_balls.my_pose.theta;
            moving_balls.teleport(moving_balls.my_pose.x,moving_balls.my_pose.y, targetAngle);
            ros::Duration(0.5).sleep();//these are to fix potential bugs when a turtle is spawned in
        }

        if(contact == true){
            double targetAngle = M_PI*2 - moving_balls.my_pose.theta;
            moving_balls.teleport(moving_balls.my_pose.x,moving_balls.my_pose.y, targetAngle);
            ros::Duration(0.5).sleep();//these are to fix potential bugs when a turtle is spawned in
            speed = speed + 0.1;
        }

        moving_balls.move(speed,0.0);
        ros::spinOnce();
        }
    return 0;
}
