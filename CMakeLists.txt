cmake_minimum_required(VERSION 3.7)
PROJECT(ChaosGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

add_executable(ChaosGame main.cpp Point.cpp Point.h)

target_link_libraries(ChaosGame -mwindows glut32.lib -lopengl32 -lglu32)