#include "difference_of_objects.h"
#include "object_interface.hpp"
#include <algorithm>

float difference_of_objects::distance_to_surface(float x2, float y2, float z2){
    return std::max(object_one->distance_to_surface(x2, y2, z2), -object_two->distance_to_surface(x2, y2, z2));
}

uint32_t difference_of_objects::get_color(float x2, float y2, float z2){
    return object_one->get_color(x2, y2, z2);
}

difference_of_objects::difference_of_objects(object_interface *object_one, object_interface *object_two){
    this->object_one = object_one;
    this->object_two = object_two;
}