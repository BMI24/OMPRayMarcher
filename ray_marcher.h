#ifndef OMPRM_RAY_MARCHER_H
#define OMPRM_RAY_MARCHER_H
#include "object_interface.hpp"
#include "light.h"

void render(const int image_x_size, const int image_y_size, uint8_t* image, object_interface** object_array,
        int object_array_length, light** lights, int light_length, float camera_x_pos, float camera_y_pos,
        float camera_z_pos, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y,
        float scale_z, float fov, float far_clip);

#endif //OMPRM_RAY_MARCHER_H
