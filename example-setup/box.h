#ifndef OMPRM_BOX_H
#define OMPRM_BOX_H

#include <cmath>
#include "../object_interface.hpp"
#include <immintrin.h>

class box : public object_interface{
private:
    union aligned_data{
        __m128 vec;
        float arr[4];
    };
    aligned_data vars;
    aligned_data lengths;
    uint32_t color;
public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint32_t get_color(float x2, float y2, float z2) override;

    box(float x, float y, float z, float x_length, float y_length, float z_length, uint32_t color);
};

#endif
