//
// Created by BMI24 on 23.01.2020.
//

#ifndef OMPRM_SPHERE_H
#define OMPRM_SPHERE_H

#include <cstdint>
#include "object_interface.hpp"

class sphere : public object_interface {
private:
    float x, y, z, radius;
    uint32_t color;
public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint32_t get_color() override;

    sphere(float x, float y, float z, float radius, uint32_t color);
};
#endif //OMPRM_SPHERE_H
