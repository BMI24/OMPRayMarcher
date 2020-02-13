# OMP Raymarcher

C++14 library which uses the ray marching approach for generating images.

## General Information

* CPU-bound rendering library 
* uses OOP principles for describing the scene 
* not a performance competitor for GPU approaches
* study to create a flexible and comprehensible implementation
* ray marching implementation: sphere tracing by John C. Hart with some additional optimizations
* lighting: phong lighting model

## How to use

Add following library files to your project:
* light.h
* light.cpp
* object_interface.hpp
* ray_marcher.h
* ray_marcher.cpp

Add the files to your cmake, also include OpenMP.  
CMake 3.9+ Syntax:
```
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(YOUR_TARGET PUBLIC OpenMP::OpenMP_CXX)
endif()
```


Input:
* Image size
* objects
* lights objects
* ambient color
* camera properties (position, rotation, scale)
* field of view
* far clip (furthest distance visible to camera)

Output:
* pixel array (row major) with each pixel in RGBA format

An example usage of the library is included in the example-setup folder.