cmake_minimum_required(VERSION 2.8)

project(kmeans)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

set(KMEANS_SRCS
kmeans.cpp
)

add_executable(kmeans
	${KMEANS_SRCS}
)
