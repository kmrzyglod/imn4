cmake_minimum_required(VERSION 3.5)
project(imn4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FlagMatrix.h imnmath.h Point.h imnmath.h Point.h Relaxation.h IntegralGraphPoint.h PoiseuilleFlow.h FlowWithObstacle.h)
add_executable(imn4 ${SOURCE_FILES})