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
    uint32_t color;
public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint32_t get_color() override;

    box(float x, float y, float z, float x_length, float y_length, float z_length, uint32_t color);
};

#endif
