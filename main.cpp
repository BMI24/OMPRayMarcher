#include <iostream>
#include "ray_marcher.h"
#include "bitmap_image.hpp"
#include "sphere.h"
#include "box.h"
#include "object_interface.hpp"
#include "light.h"
#include <chrono>

int main() {
    const std::string file_name = "raymarch.bmp";
    constexpr int image_x_size = 500;
    constexpr int image_y_size = 500;
    sphere sphere_one(9, -5, 5, 2, 0xFF000000);
    sphere sphere_two(6, 2, -1, 1.5, 0x00FF0000);
    box box_one(7,-2,-3,1,2,2, 0x0000FF00);
    box box_two(8,4,3,1,2.5,1.25, 0x6400FF00);
    std::vector<object_interface*> objects = {&box_one, &box_two, &sphere_one, &sphere_two};
    light light_one(3, -3, 3, .7, .7, .7);
    light light_two(2, 10, -4, 0.9, 0.9, 0.9);
    std::vector<light*> lights = {&light_one, &light_two};
    //x nach vorne(+)/hinten(-)
    //y nach oben(+)/unten(-)
    //z nach links(-)/rechts(+)

    std::vector<uint8_t> image(image_x_size * image_y_size * 3,0);
    auto start = std::chrono::steady_clock::now();
        render(image_x_size, image_y_size, image.data(), objects.data(), objects.size(), lights.data(), lights.size(),
                0, 0, 0, 0, -90, 0, 1, 1, 1, 90, 20);
    auto end = std::chrono::steady_clock::now();
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

    std::cout << "Wrote image to " << file_name
        << ", took " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << " ms." << std::endl;

    return 0;
}