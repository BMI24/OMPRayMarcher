#include "union_of_objects.h"
#include "object_interface.hpp"
#include <algorithm>

float union_of_objects::distance_to_surface(float x2, float y2, float z2){
    return std::min(object_one->distance_to_surface(x2, y2, z2), object_two->distance_to_surface(x2, y2, z2));
}

uint8_t union_of_objects::get_color_r(){
    return object_one->get_color_r();
}

uint8_t union_of_objects::get_color_g(){
    return object_one->get_color_g();
}

uint8_t union_of_objects::get_color_b(){
    return object_one->get_color_b();
}

union_of_objects::union_of_objects(object_interface *object_one, object_interface *object_two){
    this->object_one = object_one;
    this->object_two = object_two;
}