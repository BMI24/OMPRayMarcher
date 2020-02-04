//
// Created by BMI24 on 28.01.2020.
//

#include "fractal.h"
#include <cmath>


fractal::fractal(float x, float y, float z, int iter, float scale, uint32_t color, float rotation)
{
    fractal::x = x;
    fractal::y = y;
    fractal::z = z;
    fractal::iter = iter;
    fractal::scale = scale;
    fractal::color = color;
    float sinrotation=std::sin(rotation * 0.5f);
    float cosrotation=std::cos(rotation * 0.5f);
    mat3x3 rotMatrix = mat3x3(
            cosrotation, -sinrotation, 0.0f,
            sinrotation, cosrotation, 0.0f,
            0.0f, 0.0f, 1.0f
    );

    mat3x3 rotMatrix2 = mat3x3(
            cosrotation, 0.0f, -sinrotation,
            0.0f, 1.0f, 0.0f,
            sinrotation, 0.0f, cosrotation
    );

    vert1 = rotMatrix * rotMatrix2 * vec3(1.0f, 1.0f, 1.0f);
    vert2 = rotMatrix * rotMatrix2 * vec3(-1.0f, 1.0f, -1.0f);
    vert3 = rotMatrix * rotMatrix2 * vec3(1.0f, -1.0f, -1.0f);
    vert4 = rotMatrix * rotMatrix2 * vec3(-1.0f, -1.0f, 1.0f);
}

float fractal::distance_to_surface(float px, float py, float pz) {
    vec3 p(px - x, py - y, pz - z);
    float smallest_dist, local_dist;
    vec3* nearest_vert;
    for (int i = 0; i < iter; ++i) {
        //find nearest vertex
        nearest_vert = &vert1;
        smallest_dist = (p - vert1).qlength();

        local_dist = (p - vert2).qlength();
        if (local_dist < smallest_dist)
        {
            nearest_vert = &vert2;
            smallest_dist=local_dist;
        }

        local_dist = (p - vert3).qlength();
        if (local_dist < smallest_dist)
        {
            nearest_vert = &vert3;
            smallest_dist=local_dist;
        }

        local_dist = (p - vert4).qlength();
        if (local_dist < smallest_dist)
        {
            nearest_vert = &vert4;
        }

        p = p * scale - *nearest_vert * (scale - 1.f);
    }

    return p.length() * std::pow(scale, float(-iter));
}

uint32_t fractal::get_color(float, float, float)  {
    return color;
}