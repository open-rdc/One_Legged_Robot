cmake_minimum_required(VERSION 2.8)

project(kmeans_Clustering)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)


set(kmeans_clustering
kmeansfiveparamater.cpp
kmeansfiveparamater.h
)

add_executable(kmeans_clustering
	${kmeans_clustering}
)

