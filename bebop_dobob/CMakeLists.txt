cmake_minimum_required(VERSION 3.0.0)
project(bebop_dobob)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
	geometry_msgs
	roscpp
	std_msgs
	sensor_msgs
	bebop_msgs
	cv_bridge
#	image_transport
)

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

#generate_messages(
#  DEPENDENCIES
#  geometry_msgs
#  std_msgs
#  sensor_msgs
#  bebop_msgs
#)


catkin_package(
	INCLUDE_DIRS include
	LIBRARIES bebop_dobob
	CATKIN_DEPENDS geometry_msgs roscpp std_msgs sensor_msgs bebop_msgs cv_bridge
# image_transport
	DEPENDS ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY}
)

include_directories(include
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
	${catkin_INCLUDE_DIRS})

link_directories(${SDL2_LIBRARY_DIRS}
	${SDL2_TTF_LIBRARY_DIRS}
	${catkin_LIBRARY_DIRS})


add_executable( bebop_dobob src/Events.cpp src/Input.cpp src/ManualControl.cpp src/StateTracker.cpp src/main.cpp)
#src/Window.cpp src/GUI.cpp src/Patroller.cpp
#add_executable( webcam_dobob src/WebcamPublisher.cpp)
target_link_libraries( bebop_dobob
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${catkin_LIBRARIES}
)

#target_link_libraries( webcam_dobob
#	${catkin_LIBRARIES}
#)
