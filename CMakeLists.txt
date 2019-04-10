cmake_minimum_required(VERSION 3.13)
project(MK)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Util)
add_subdirectory(Nodes)

add_executable(mk
        Builder.h
        Builder.cpp

        main.cpp)
target_link_libraries(mk mk-util mk-nodes)
