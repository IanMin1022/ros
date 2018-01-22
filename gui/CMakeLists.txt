cmake_minimum_required(VERSION 2.8.3)
project(gui)

add_definitions(-std=c++11)
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
	geometry_msgs
	roscpp
	std_msgs
	bebop_msgs
	sensor_msgs
)

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES gui
	CATKIN_DEPENDS geometry_msgs roscpp std_msgs sensor_msgs bebop_msgs
	DEPENDS ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY}
)

include_directories(include
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
	${catkin_INCLUDE_DIRS})

link_directories(${SDL2_LIBRARY_DIRS}
	${SDL2_TTF_LIBRARY_DIRS}
	${catkin_LIBRARY_DIRS})

add_executable( gui src/Window.cpp src/GUI.cpp src/main.cpp src/Events.cpp src/Input.cpp src/State.cpp )

target_link_libraries( gui
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${catkin_LIBRARIES}
)
