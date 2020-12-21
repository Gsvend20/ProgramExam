
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***

//https://github.com/ros/ros_tutorials/blob/cd4ed467c7bc4b86512fed1f82346b95bf313a31/turtlesim/tutorials/teleop_turtle_key.cpp
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <sstream>


#include <turtlesim/Spawn.h>
#include <turtlesim/SetPen.h>
//VARIBLES






ros::NodeHandle *pointer_n;

void spawnWalls() //Spawning turtles to control
{

  ros::ServiceClient spawn_client = pointer_n->serviceClient<turtlesim::Spawn>("/spawn");
  turtlesim::Spawn wall_spawn_msg;

  //Spawning first wall
  wall_spawn_msg.request.name = "turtle2";
  wall_spawn_msg.request.x = 1.544445;
  wall_spawn_msg.request.y = 5.544445;
  spawn_client.call(wall_spawn_msg);

  //Spawning second wall
  wall_spawn_msg.request.name = "turtle3";
  wall_spawn_msg.request.x = 9.544445;
  wall_spawn_msg.request.y = 5.544445;
  spawn_client.call(wall_spawn_msg);
}

void stopDraw() //Stops the turtles from drawing lines when they move
{
  //Sets up two service clients, one for each wall turtle
  ros::ServiceClient pen_client2 = pointer_n->serviceClient<turtlesim::SetPen>("/turtle2/set_pen");
  ros::ServiceClient pen_client3 = pointer_n->serviceClient<turtlesim::SetPen>("/turtle3/set_pen");

  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client2.call(pen_srv);
  pen_client3.call(pen_srv);
}

//SUB CALLBACKS


// Creating Publisher and subscriber 



int main(int argc, char *argv[]){
ros::init(argc,argv, "Walls");

  ros::NodeHandle n;
  pointer_n = &n;

  spawnWalls();

    while(ros::ok()){
    
    }
  return 0;
}
