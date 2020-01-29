#include <cmath>
#include "box.h"

inline float length(float x1, float y1, float z1) {
    return sqrtf(
            powf(x1, 2)
            + powf(y1, 2)
            + powf(z1, 2));
}

float box::distance_to_surface(float x2, float y2, float z2) {
    float x_distance = fabsf(x-x2) - x_length;
    float y_distance = fabsf(y-y2) - y_length;
    float z_distance = fabsf(z-z2) - z_length;

    return std::fmin(std::fmax(x_distance, std::fmax(y_distance, z_distance)), 0.f)
           + length(std::fmax(x_distance, 0.f), std::fmax(y_distance,0.f), std::fmax(z_distance,0.f));
}


uint32_t box::get_color() {
    return color;
}

box::box(float x, float y, float z, float x_length, float y_length, float z_length, uint32_t color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->x_length = x_length;
    this->y_length = y_length;
    this->z_length = z_length;
    this->color = color;
}