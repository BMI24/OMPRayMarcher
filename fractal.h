//
// Created by BMI24 on 28.01.2020.
//

#ifndef OMPRM_FRACTAL_H
#define OMPRM_FRACTAL_H


#include "object_interface.hpp"

class fractal : public object_interface {
private:
    int iter;
    float x, y, z, scale;
    uint32_t color;
public:
    fractal(float x, float y, float z, int iter, float scale, uint32_t color);
    float distance_to_surface(float x, float y, float z) override;
    uint32_t get_color() override;
};


#endif //OMPRM_FRACTAL_H
