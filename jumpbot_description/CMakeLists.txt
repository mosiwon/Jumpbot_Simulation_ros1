cmake_minimum_required(VERSION 2.8.3)

project(jumpbot_description)

find_package(catkin REQUIRED)

catkin_package()

find_package(roslaunch)

foreach(dir config meshes urdf rviz)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
