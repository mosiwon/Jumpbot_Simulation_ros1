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


add_executable(start_script src/jumpbot_joint_state_publisher.cpp)

target_link_libraries(start_script ${catkin_LIBRARIES})
