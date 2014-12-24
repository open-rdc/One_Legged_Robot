cmake_minimum_required(VERSION 2.8)

project(RobotString)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

set(ROBOTSTRING_SRCS
robot_string.cpp

)

add_executable(RobotString
	${ROBOTSTRING_SRCS}
)
