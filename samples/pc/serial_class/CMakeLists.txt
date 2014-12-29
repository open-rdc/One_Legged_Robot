cmake_minimum_required(VERSION 2.8)

project(SerialClass)

set(ENV{Boost_DIR})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system thread filesystem)

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

set(SC_SRCS
Serial.cpp	main.cpp

Serial.h
)

add_executable(SerialClass
	${SC_SRCS}
)

target_link_libraries(SerialClass
	${Boost_LIBRARIES}
)
