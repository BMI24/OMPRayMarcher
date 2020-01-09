#include <iostream>
#include <cmath>
#include <string.h>
#include "ray_marcher.h"
#include "bitmap_image.hpp"
#include "sphere.cpp"
#include "box.cpp"
#include "object_interface.cpp"

int main() {
    const std::string file_name = "raymarch.bmp";
    constexpr int image_x_size = 500;
    constexpr int image_y_size = 500;
    sphere sphere_one(9, 6, 6, 2, 255, 0, 0);
    sphere sphere_two(6, -2, -1, 1.5, 0, 255, 0);
    box box_one(7,2,-3,1,2,2,0,0,255);
    box box_two(8,2,-2,1,2.5,1.25,100,0,255);
    std::vector<object_interface*> objects = {&box_one, &box_two, &sphere_one, &sphere_two};
    //x nach vorne(+)/hinten(-)
    //y nach oben(-)/unten(+)
    //z nach links(-)/rechts(+)

    std::vector<uint8_t> image(image_x_size * image_y_size * 3,0);

    render(image_x_size, image_y_size, image.data(), objects.data(), objects.size());

    bitmap_image image_file(image_x_size, image_y_size);

    for (int y = 0; y < image_y_size; ++y) {
        for (int x = 0; x < image_x_size; ++x) {
            image_file.set_pixel(x,y,
                    image[3*(y*image_x_size+x)+0],
                    image[3*(y*image_x_size+x)+1],
                    image[3*(y*image_x_size+x)+2]);
        }
    }

    image_file.save_image(file_name);

    std::cout << "Wrote image to " << file_name << std::endl;

    return 0;
}