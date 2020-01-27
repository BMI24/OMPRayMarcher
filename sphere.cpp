#include <cstdint>
#include <cmath>
#include "sphere.h"

inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrtf(
            powf(x1 - x2, 2)
            + powf(y1 - y2, 2)
            + powf(z1 - z2, 2));
}

float sphere::distance_to_surface(float x2, float y2, float z2) {
    float distance = distance_between(x, y, z, x2, y2, z2) - radius;
    return distance;
}

uint8_t sphere::get_color_r()  {
    return color_r;
}

uint8_t sphere::get_color_g() {
    return color_g;
}

uint8_t sphere::get_color_b() {
    return color_b;
}

sphere::sphere(float x, float y, float z, float radius, uint8_t color_r, uint8_t color_g, uint8_t color_b){
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->color_r = color_r;
    this->color_g = color_g;
    this->color_b = color_b;
}