#ifndef OMPRM_BOX_CPP
#define OMPRM_BOX_CPP

#include <cmath>
#include "object_interface.cpp"

class box : public object_interface{
private:
    float x, y, z, x_length, y_length, z_length;
    uint8_t color_r, color_g, color_b;

public:
    float distance_to_surface(float x2, float y2, float z2) override {
        float x_distance = fabs(x-x2) - x_length;
        float y_distance = fabs(y-y2) - y_length;
        float z_distance = fabs(z-z2) - z_length;

        return std::fmin(std::fmax(x_distance, std::fmax(y_distance, z_distance)), 0.0)
                + length(std::fmax(x_distance, 0), std::fmax(y_distance,0), std::fmax(z_distance,0));
    }

    static inline float length(float x1, float y1, float z1) {
        return sqrt(
                pow(x1, 2)
                + pow(y1, 2)
                + pow(z1, 2));
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

    box(float x, float y, float z, float x_length, float y_length, float z_length,
            uint8_t color_r, uint8_t color_g, uint8_t color_b){
        this->x = x;
        this->y = y;
        this->z = z;
        this->x_length = x_length;
        this->y_length = y_length;
        this->z_length = z_length;
        this->color_r = color_r;
        this->color_g = color_g;
        this->color_b = color_b;
    }
};

#endif