cmake_minimum_required(VERSION 2.8)

project(GeneticAlgorithm)

set(ENV{Boost_DIR})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system thread filesystem date_time)

IF(WIN32)
	add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
ENDIF(WIN32)

IF(UNIX)
	add_definitions(
		"-std=c++11"
		${Boost_LIB_DIAGNOSTIC_DEFINITIONS}
	)
ENDIF(UNIX)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

set(GA_SRCS
GeneticAlgorithm.cpp	Serial.cpp	Utility.cpp	FileManager.cpp

GeneticAlgorithm.h	Serial.h	parameter.h	Utility.h	FileManager.h
)

add_executable(GeneticAlgorithm
	${GA_SRCS}
)

target_link_libraries(GeneticAlgorithm
	${Boost_LIBRARIES}
)
