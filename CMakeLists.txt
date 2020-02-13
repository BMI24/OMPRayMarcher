cmake_minimum_required(VERSION 3.15)
project(omprm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -ffast-math -ofast -g")

add_executable(omprm example-setup/main.cpp ray_marcher.h example-setup/bitmap_image.hpp ray_marcher.cpp example-setup/sphere.cpp example-setup/box.cpp object_interface.hpp light.cpp example-setup/sphere.h example-setup/box.h light.h example-setup/difference_of_objects.cpp example-setup/difference_of_objects.h example-setup/union_of_objects.cpp example-setup/union_of_objects.h example-setup/intersection_of_objects.cpp example-setup/intersection_of_objects.h example-setup/fractal.cpp example-setup/fractal.h)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(omprm PUBLIC OpenMP::OpenMP_CXX)
endif()