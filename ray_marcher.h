#ifndef OMPRM_RAY_MARCHER_H
#define OMPRM_RAY_MARCHER_H
#include "object_interface.cpp"
#include "light.cpp"

void render(const int image_x_size, const int image_y_size, uint8_t* image, object_interface** object_array,
        int object_array_length, light** lights, int light_length);

#endif //OMPRM_RAY_MARCHER_H
