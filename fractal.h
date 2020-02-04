//
// Created by BMI24 on 28.01.2020.
//

#ifndef OMPRM_FRACTAL_H
#define OMPRM_FRACTAL_H


#include "object_interface.hpp"
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

    vec3() {
        x = 0;
        y = 0;
        z = 0;
    }

    inline float length() const {
        return std::sqrt(x*x+y*y+z*z);
    }

    inline float qlength() const {
        return x*x + y*y + z*z;
    }
};

struct mat3x3
{
    float* matrix;

    mat3x3()
    {
        matrix = new float[9]();
    }

    mat3x3(float v0, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8)
    {
        matrix = new float[9];
        matrix[0] = v0; matrix[1] = v1; matrix[2] = v2;
        matrix[3] = v3; matrix[4] = v4; matrix[5] = v5;
        matrix[6] = v6; matrix[7] = v7; matrix[8] = v8;
    }

    ~mat3x3()
    {
        delete[] matrix;
    }

    inline mat3x3 operator*(const mat3x3& b) const {
        mat3x3 result;
        for(int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result.matrix[i * 3 + j] = 0;
                for (int k = 0; k < 3; ++k) {
                    result.matrix[i * 3 + j] += matrix[i * 3 + k] * b.matrix[k * 3 + j];
                }
            }
        }
        return result;
    }

    inline vec3 operator*(const vec3& b) const{
        constexpr float b4 = 1;
        return {
                b.x*matrix[0]+b.y*matrix[1]+b.z*matrix[2],
                b.x*matrix[3]+b.y*matrix[4]+b.z*matrix[5],
                b.x*matrix[6]+b.y*matrix[7]+b.z*matrix[8]};
    }
};


class fractal : public object_interface {
private:
    int iter;
    float x, y, z, scale;
    uint32_t color;
    vec3 vert1, vert2, vert3, vert4;
public:
    fractal(float x, float y, float z, int iter, float scale, uint32_t color, float rotation);
    float distance_to_surface(float x, float y, float z) override;
    uint32_t get_color(float x2, float y2, float z2) override;
};


#endif //OMPRM_FRACTAL_H
