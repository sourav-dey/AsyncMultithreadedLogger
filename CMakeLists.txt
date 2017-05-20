cmake_minimum_required(VERSION 3.7)
project(Logger)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/Logger.h Logger.cpp include/WorkerQueue.h include/ConsumerThread.h include/Thread.h Thread.cpp include/WorkItem.h)
add_executable(Logger ${SOURCE_FILES})