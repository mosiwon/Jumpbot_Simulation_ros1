cmake_minimum_required(VERSION 2.8.3)
project(jumpbot_joint_controller)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED
 catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    geometry_msgs
    sensor_msgs
    message_generation
  )



catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

install(DIRECTORY src
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


add_executable(arm_rotate src/arm_rotate.cpp)

target_link_libraries(arm_rotate ${catkin_LIBRARIES})
