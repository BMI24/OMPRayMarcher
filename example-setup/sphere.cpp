#include <cstdint>
#include <cmath>
#include "sphere.h"

inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xdiff = x1 - x2;
    float ydiff = y1 - y2;
    float zdiff = z1 - z2;
    return std::sqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
}

float sphere::distance_to_surface(float x2, float y2, float z2) {
    float distance = distance_between(x, y, z, x2, y2, z2) - radius;
    return distance;
}

uint32_t sphere::get_color(float, float, float)  {
    return color;
}

sphere::sphere(float x, float y, float z, float radius, uint32_t color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->color = color;
}