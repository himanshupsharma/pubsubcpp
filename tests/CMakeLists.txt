project(pubsub_unittests)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
	../src
	../gtest-1.7.0/include
)

set(SRC_LIST
    test.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} gtest_main pubsub)
