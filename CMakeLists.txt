cmake_minimum_required(VERSION 2.8.3)
project(testExam)

add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  turtlesim
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_first_pkg
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(paddles src/paddles.cpp)
add_executable(ball src/ball.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(paddles
  ${catkin_LIBRARIES}
)

target_link_libraries(ball
  ${catkin_LIBRARIES}
)

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
install(TARGETS paddles ball
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)