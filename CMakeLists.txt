cmake_minimum_required(VERSION 3.13.4)
project(graphs-1-electronico-y-2-cientificos)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)



add_executable(graphs-1-electronico-y-2-cientificos main.cpp edge.h graph.h node.h read.h tester.cpp tester.h)