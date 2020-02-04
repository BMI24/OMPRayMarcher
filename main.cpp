#include <iostream>
#include "ray_marcher.h"
#include "bitmap_image.hpp"
#include "sphere.h"
#include "box.h"
#include "object_interface.hpp"
#include "light.h"
#include <chrono>
#include "difference_of_objects.h"
#include "union_of_objects.h"
#include "intersection_of_objects.h"
#include "fractal.h"

int main() {
    constexpr int image_x_size = 1000;
    constexpr int image_y_size = 1000;
    /*sphere sphere_one(7, 3, -3, 2, 0XFF000000);
    box box_one(8, -2, -2, 1, 2, 2, 0X0000FF00);

    box box_five(6, 0, 5, 2, 1, 1, 0X64963200);
    box box_six(6, 0, 5, 1, 2, 1, 0X00000000);
    box box_seven(6, 0, 5, 1, 1, 2, 0X00000000);
    union_of_objects box_box_one(&box_five, &box_six);
    union_of_objects box_box_two(&box_box_one, &box_seven);
    std::vector<object_interface*> objects = {&box_one, &sphere_one, &box_box_two};*/
    fractal f(0,0,0,10, 2, 0xFFFFFFFF, 0.1);
    std::vector<object_interface*> objects = {&f};
    light light_one(3, -3, 3, .35, .35, .35);
    light light_two(2, 10, -4, 0.45, 0.45, 0.45);
    std::vector<light*> lights = {&light_one, &light_two};
    //x nach vorne(+)/hinten(-)
    //y nach oben(+)/unten(-)
    //z nach links(-)/rechts(+)

    constexpr int iter = 1;
    std::vector<uint32_t> image(image_x_size * image_y_size,0);
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < iter; ++i) {
        render(image_x_size, image_y_size, image.data(), objects.data(), objects.size(), lights.data(), lights.size(),
               0x2F2F2F00, 0, 0, 2, 0, 0, 0, 1, 1, 1, 90, 20);
    }
    auto end = std::chrono::steady_clock::now();

    const std::string file_name = "raymarch.bmp";
    bitmap_image image_file(image_x_size, image_y_size);

    for (int y = 0; y < image_y_size; ++y) {
        for (int x = 0; x < image_x_size; ++x) {
            image_file.set_pixel(x,y,
                    image[y*image_x_size+x] >> 24u,
                    image[y*image_x_size+x] >> 16u & 0xFFu,
                    image[y*image_x_size+x] >> 8u & 0xFFu);
        }
    }

    image_file.save_image(file_name);

    std::cout << "Wrote image to " << file_name
        << ", took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / iter<< " ms."
        << std::endl;

    return 0;
}