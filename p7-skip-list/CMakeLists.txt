cmake_minimum_required(VERSION 3.30)
project(p7_skip_list)

set(CMAKE_CXX_STANDARD 20)

add_executable(p7_skip_list main.cc
        apal/skip_list.cc
        apal/skip_list.h
        apal/skip_list_node.h
        apal/skip_list_node.cc
)
