#ifndef OMPRM_SPHERE_CPP
#define OMPRM_SPHERE_CPP

#include <cstdint>
#include <cmath>
#include "object_interface.cpp"

class sphere : public object_interface{
private:
    float x, y, z, radius;
    uint8_t color_r, color_g, color_b;

public:
    float distance_to_surface(float x2, float y2, float z2) override {

        float distance = distance_between(x, y, z, x2, y2, z2) - radius;

        return distance;
    }

    static inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2) {
        return sqrt(
                pow(x1 - x2, 2)
                + pow(y1 - y2, 2)
                + pow(z1 - z2, 2));
    }

    uint8_t get_color_r() override {
        return color_r;
    }

    uint8_t get_color_g() override {
        return color_g;
    }

    uint8_t get_color_b() override {
        return color_b;
    }

    sphere(float x, float y, float z, float radius, uint8_t color_r, uint8_t color_g, uint8_t color_b){
        this->x = x;
        this->y = y;
        this->z = z;
        this->radius = radius;
        this->color_r = color_r;
        this->color_g = color_g;
        this->color_b = color_b;
    }
};

#endif //OMPRM_SPHERE_CPP