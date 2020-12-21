
//  *** Author: Group B336  ***
//  *** Project: Miniproject for P1***
//  *** Node: --//--***
//  *** Created: 03-12-2020***
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> //Turtlesim movement

//Following inclusions are used for the KeyboardReader Class
//https://github.com/ros/ros_tutorials/blob/cd4ed467c7bc4b86512fed1f82346b95bf313a31/turtlesim/tutorials/teleop_turtle_key.cpp
#include <signal.h>
#include <stdio.h>
#ifndef _WIN32
# include <termios.h>
# include <unistd.h>
#else
# include <windows.h>
#endif

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
//#define KEYCODE_Q 0x71

//KeyboardReader class from https://github.com/ros/ros_tutorials/blob/cd4ed467c7bc4b86512fed1f82346b95bf313a31/turtlesim/tutorials/teleop_turtle_key.cpp
class KeyboardReader
{
public:
  KeyboardReader()
#ifndef _WIN32
    : kfd(0)
#endif
  {
#ifndef _WIN32
    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    struct termios raw;
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
#endif
  }
  void readOne(char * c)
  {
#ifndef _WIN32
    int rc = read(kfd, c, 1);
    if (rc < 0)
    {
      throw std::runtime_error("read failed");
    }
#else
    for(;;)
    {
      HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
      INPUT_RECORD buffer;
      DWORD events;
      PeekConsoleInput(handle, &buffer, 1, &events);
      if(events > 0)
      {
        ReadConsoleInput(handle, &buffer, 1, &events);
        if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
        {
          *c = KEYCODE_LEFT;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_UP)
        {
          *c = KEYCODE_UP;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
        {
          *c = KEYCODE_RIGHT;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
        {
          *c = KEYCODE_DOWN;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x42)
        {
          *c = KEYCODE_B;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x43)
        {
          *c = KEYCODE_C;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x44)
        {
          *c = KEYCODE_D;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x45)
        {
          *c = KEYCODE_E;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x46)
        {
          *c = KEYCODE_F;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x47)
        {
          *c = KEYCODE_G;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x51)
        {
          *c = KEYCODE_Q;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x52)
        {
          *c = KEYCODE_R;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x54)
        {
          *c = KEYCODE_T;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == 0x56)
        {
          *c = KEYCODE_V;
          return;
        }
      }
    }
#endif
  }
  void shutdown()
  {
#ifndef _WIN32
    tcsetattr(kfd, TCSANOW, &cooked);
#endif
  }
private:
#ifndef _WIN32
  int kfd;
  struct termios cooked;
#endif
};

KeyboardReader input; //

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
