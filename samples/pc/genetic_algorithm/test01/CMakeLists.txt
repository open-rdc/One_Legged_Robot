cmake_minimum_required(VERSION 2.8)

project(GeneticAlgorithm)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

set(GA_SRCS
chromosome.cpp	main.cpp
chromosome.h
)

add_executable(GeneticAlgorithm
	${GA_SRCS}
)
