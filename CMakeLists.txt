cmake_minimum_required(VERSION 3.15)
project(omprm)

set(CMAKE_CXX_STANDARD 14)

add_executable(omprm main.cpp ray_marcher.h bitmap_image.hpp ray_marcher.cpp sphere.cpp box.cpp object_interface.cpp light.cpp)