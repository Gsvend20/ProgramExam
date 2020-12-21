
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> //Turtlesim movement

//#include <sstream> //Why is this here?

#include <iostream>

//Used for reading keyboard input
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

//Used to setup turtles and get info on them
#include <turtlesim/Spawn.h>
#include <turtlesim/SetPen.h>
#include <turtlesim/Pose.h>

ros::NodeHandle *pointer_n;

void spawnWalls() //Spawning turtles to control
{

  ros::ServiceClient spawn_client = pointer_n->serviceClient<turtlesim::Spawn>("/spawn");
  turtlesim::Spawn wall_spawn_msg;

  //Spawning first wall
  wall_spawn_msg.request.name = "turtle2";
  wall_spawn_msg.request.x = 1.544445;
  wall_spawn_msg.request.y = 5.544445;
  wall_spawn_msg.request.theta = M_PI/2;
  spawn_client.call(wall_spawn_msg);

  //Spawning second wall
  wall_spawn_msg.request.name = "turtle3";
  wall_spawn_msg.request.x = 9.544445;
  wall_spawn_msg.request.y = 5.544445;
  wall_spawn_msg.request.theta = M_PI/2;
  spawn_client.call(wall_spawn_msg);
}

void stopDraw() //Stops the turtles from drawing lines when they move (maybe unneeded)
{
  //Sets up two service clients, one for each wall turtle
  ros::ServiceClient pen_client2 = pointer_n->serviceClient<turtlesim::SetPen>("/turtle2/set_pen");
  ros::ServiceClient pen_client3 = pointer_n->serviceClient<turtlesim::SetPen>("/turtle3/set_pen");

  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client2.call(pen_srv);
  pen_client3.call(pen_srv);
}

//From https://github.com/methylDragon/teleop_twist_keyboard_cpp/blob/525fb108bbe7ad2527b82cc9ebc0d461b1bdadf3/src/teleop_twist_keyboard.cpp#L81
//For non-blocking keyboard inputs
int getch(void)
{
  int ch;
  struct termios oldt;
  struct termios newt;

  // Store old settings, and copy to new settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Make required changes and apply the settings
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_iflag |= IGNBRK;
  newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
  newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &newt);

  // Get the current character
  ch = getchar();

  // Reapply old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

int main(int argc, char *argv[]){
ros::init(argc,argv, "Walls");

  ros::NodeHandle n;
  pointer_n = &n;

  spawnWalls();
  stopDraw();

  geometry_msgs::Twist turtle2Twist;
  geometry_msgs::Twist turtle3Twist;
  ros::Publisher turtle2Move = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1);
  ros::Publisher turtle3Move = n.advertise<geometry_msgs::Twist>("/turtle3/cmd_vel", 1);

  int key;
  printf("Control turtles with w/s and o/l \n\nPress ctrl+c to quit\n");

  while(ros::ok())
  {
    key = getch();
    switch (key)
    {
      case 119: //119 = w
        turtle2Twist.linear.x = 1;
        turtle2Move.publish(turtle2Twist);
        break;

      case 115: //115 = s
        turtle2Twist.linear.x = -1;
        turtle2Move.publish(turtle2Twist);
        break;

      case 111: //111 = o
        turtle3Twist.linear.x = 1;
        turtle3Move.publish(turtle3Twist);
        break;

      case 108: //108 = l
        turtle3Twist.linear.x = -1;
        turtle3Move.publish(turtle3Twist);
        break;

      case 3: //Exit program by pressing ctrl+c
        return 0;

      default:
        std::cout << "Error! Wrong key pressed(" << key << ")" << std::endl
        << "Press w/s to control first turtle or o/l to control the second." << std::endl;
    }
    ros::spinOnce();
  }
  return 0;
}
