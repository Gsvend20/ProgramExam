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


add_executable(walls src/walls.cpp)
add_executable(ball src/ball.cpp)

target_link_libraries(walls
  ${catkin_LIBRARIES}
)

target_link_libraries(ball
  ${catkin_LIBRARIES}
)

install(TARGETS walls ball
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)