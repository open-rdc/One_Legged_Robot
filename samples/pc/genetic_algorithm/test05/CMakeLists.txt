cmake_minimum_required(VERSION 2.8)

project(GeneticAlgorithm)

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

set(GA_SRCS
genetic_algorithm.cpp	Serial.cpp

Serial.h	parameter.h
)

set(Kmeans_Clustering
kmeansfiveparamater.cpp
kmeansfiveparamater.h
)

add_executable(GeneticAlgorithm
	${GA_SRCS}
)

add_executable(Kmeans_Clustering
	${Kmeans_Clustering}
)

target_link_libraries(GeneticAlgorithm
	${Boost_LIBRARIES}
)
