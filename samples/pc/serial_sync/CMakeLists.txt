cmake_minimum_required(VERSION 2.8)

project(serial_sync)

set(ENV{Boost_DIR})
set(Boost_ADDITIONAL_VERSIONS "1.54" "1.54.0")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.54.0 COMPONENTS system thread filesystem)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${BOOST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

set(SERIAL_SRCS
serial_sync.cpp
)

add_executable(serial
	${SERIAL_SRCS}
)

target_link_libraries(serial
	${Boost_LIBRARIES}
)