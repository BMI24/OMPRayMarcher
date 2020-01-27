//
// Created by BMI24 on 27.01.2020.
//

#ifndef OMPRM_BOX_H
#define OMPRM_BOX_H

#include <cmath>
#include "object_interface.hpp"

class box : public object_interface{
private:
    float x, y, z, x_length, y_length, z_length;
    uint8_t color_r, color_g, color_b;
public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint8_t get_color_r() override;

    uint8_t get_color_g() override;

    uint8_t get_color_b() override;

    box(float x, float y, float z, float x_length, float y_length, float z_length, uint8_t color_r, uint8_t color_g, uint8_t color_b);
};

#endif
