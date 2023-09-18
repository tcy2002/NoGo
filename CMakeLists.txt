cmake_minimum_required(VERSION 3.22)
project(NoGo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(NoGo
        Game_frame.cpp
        General_frame.cpp
        main.cpp
        NoGo.cpp
        NoGo.h
        NoGo_frame.h
        NoGo_high.cpp
        Opitions_frame.cpp)
