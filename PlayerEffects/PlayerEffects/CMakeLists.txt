cmake_minimum_required(VERSION 3.28)
project(PlayerEffects)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PlayerEffects
        Effect.cpp
        Effect.h
        Player.cpp
        Player.h
        PlayerEffects.cpp)
