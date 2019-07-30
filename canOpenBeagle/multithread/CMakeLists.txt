cmake_minimum_required(VERSION 3.14)
project(Capstone)

set(CMAKE_CXX_STANDARD 14)

add_executable(Capstone main.cpp Robot.cpp Robot.h Exo.cpp Exo.h Joint.cpp Joint.h cmake-build-debug/Candev.cpp cmake-build-debug/Candev.h)