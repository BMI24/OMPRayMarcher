cmake_minimum_required(VERSION 3.15)
project(omprm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -ffast-math -ofast")

add_executable(omprm main.cpp ray_marcher.h bitmap_image.hpp ray_marcher.cpp sphere.cpp box.cpp object_interface.hpp light.cpp sphere.h box.h light.h difference_of_objects.cpp difference_of_objects.h union_of_objects.cpp union_of_objects.h intersection_of_objects.cpp intersection_of_objects.h)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(omprm PUBLIC OpenMP::OpenMP_CXX)
endif()