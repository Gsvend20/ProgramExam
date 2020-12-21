
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
#include <turtlesim/Spawn.h>

//VARIBLES






ros::NodeHandle * pointer_n;

//FUNCTION CALLS
void spawn_Walls()
{
  ros::ServiceClient spawn_client = pointer_n->serviceClient<turtlesim::Spawn>("/spawn");
  turtlesim::Spawn wall_spawn_msg;

  //Spawning first wall
  wall_spawn_msg.request.name = "turtle2";
  wall_spawn_msg.request.x = 9;
  wall_spawn_msg.request.y = 5;
  spawn_client.call(wall_spawn_msg);

  //Spawning second wall
  wall_spawn_msg.request.name = "turtle3";
  wall_spawn_msg.request.x = 9;
  wall_spawn_msg.request.y = 5;
  spawn_client.call(wall_spawn_msg);
}




using namespace std;


//SUB CALLBACKS


// Creating Publisher and subscriber 



int main(int argc, char *argv[]){
ros::init(argc,argv, "Walls");

  ros::NodeHandle n;
  pointer_n = &n;

    while(ros::ok()){


    }
    
    return 0;
}
