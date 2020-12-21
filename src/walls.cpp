
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> //Turtlesim movement

#include <sstream> //Why is this here?

//Used to setup turtles and get info on them
#include <turtlesim/Spawn.h>
#include <turtlesim/SetPen.h>
#include <turtlesim/Pose.h>

//Ascii codes for used keyboard characters (all lower case)
//https://en.wikipedia.org/wiki/ASCII
#define KEYCODE_UP 0x41
#define KEYCODE_DOWN 0x42
#define KEYCODE_W 0x77
#define KEYCODE_S 0x73

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

  while(ros::ok())
  {

  }
  return 0;
}
