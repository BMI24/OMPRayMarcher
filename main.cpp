#include <iostream>
#include <cmath>
#include <string.h>
#include "ray_marcher.h"
#include "bitmap_image.hpp"

int main() {
    const std::string file_name = "sphere.bmp";

    constexpr int image_x_size = 100;
    constexpr int image_y_size = 100;
    std::vector<uint8_t> image(image_x_size * image_y_size * 3,0);

    render(image_x_size, image_y_size, image.data());

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