//
// Created by BMI24 on 28.01.2020.
//

#include "fractal.h"
#include <cmath>

struct vec3
{
    float x;
    float y;
    float z;

    inline vec3 operator+(const vec3& b) const {
        return {x+b.x, y+b.y, z+b.z};
    }

    inline vec3 operator-(const vec3& b) const {
        return {x-b.x, y-b.y, z-b.z};
    }

    inline vec3 operator*(const float s) const {
        return {x*s, y*s, z*s};
    }
    inline vec3 operator/(const float s) const {
        return {x/s, y/s, z/s};
    }

    inline vec3 operator*(const vec3& b) const {
        return {x*b.x, y*b.y, z*b.z};
    }

    vec3(float x1, float y1, float z1) {
        x = x1;
        y = y1;
        z = z1;
    }
};

inline float length(const vec3& input)
{
    return sqrtf(powf(input.x,2.f)+powf(input.y,2.f)+powf(input.z,2.f));
}

fractal::fractal(float x, float y, float z, int iter, float scale, uint32_t color)
{
    fractal::x = x;
    fractal::y = y;
    fractal::z = z;
    fractal::iter = iter;
    fractal::scale = scale;
    fractal::color = color;
}

float fractal::distance_to_surface(float px, float py, float pz) {
    vec3 p(px - x, py - y, pz - z);
    vec3 vert1 = vec3(1, 1, 1);
    vec3 vert2 = vec3(-1, -1, 1);
    vec3 vert3 = vec3(1, -1, -1);
    vec3 vert4 = vec3(-1, 1, -1);
    vec3 nearest_vert(0, 0, 0);

    float smallest_dist, local_dist;
    for (int i = 0; i < iter; ++i) {
        //find nearest vertex
        nearest_vert = vert1;
        smallest_dist = length(p - vert1);

        local_dist = length(p - vert2);
        if (local_dist < smallest_dist)
        {
            nearest_vert = vert2;
            smallest_dist=local_dist;
        }
        local_dist = length(p - vert3);

        if (local_dist < smallest_dist)
        {
            nearest_vert = vert3;
            smallest_dist=local_dist;
        }
        local_dist = length(p - vert4);

        if (local_dist < smallest_dist)
        {
            nearest_vert = vert4;
        }

        p = p * scale - nearest_vert * (scale - 1.f);
    }

    return length(p) * powf(scale, float(-iter));
}

uint32_t fractal::get_color()  {
    return color;
}