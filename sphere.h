#ifndef OMPRM_SPHERE_H
#define OMPRM_SPHERE_H

#include <cstdint>
#include "object_interface.hpp"

class sphere : public object_interface {
private:
    float x, y, z, radius;
    uint8_t color_r, color_g, color_b;
public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint8_t get_color_r() override;

    uint8_t get_color_g() override;

    uint8_t get_color_b() override;

    sphere(float x, float y, float z, float radius, uint8_t color_r, uint8_t color_g, uint8_t color_b);
};
#endif //OMPRM_SPHERE_H
