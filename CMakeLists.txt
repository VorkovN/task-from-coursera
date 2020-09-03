cmake_minimum_required(VERSION 3.17)
project(Week2)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

add_executable(Week2 hotels.cpp)
target_link_libraries(Week2 ${GTEST_LIBRARIES} pthread)
