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
    uint8_t color_r, color_g, color_b;
public:
    fractal(float x, float y, float z, int iter, float scale);
    float distance_to_surface(float x, float y, float z) override;
    uint8_t get_color_r() override;
    uint8_t get_color_g() override;
    uint8_t get_color_b() override;
};


#endif //OMPRM_FRACTAL_H
