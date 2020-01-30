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

int main() {
    const std::string file_name = "raymarch.bmp";
    constexpr int image_x_size = 1920;
    constexpr int image_y_size = 1080;
    sphere sphere_one(9, -4, -1, 2, 255, 0, 0);
    sphere sphere_two(6, 2, -1, 1.5, 0, 255, 0);
    box box_one(7,-2,-8,1,2,2,0,0,255);
    box box_two(8,4,3,1,2.5,1.25,100,0,255);

    box box_three(6, 2.5, -6, 1, 2, 2, 0, 255, 150);
    sphere sphere_three(4, 4, -7.5, 2, 0, 0, 0);
    sphere sphere_four(4, 4, -4.5, 2, 0, 0, 0);
    sphere sphere_five(4, 1, -7.5, 2, 0, 0, 0);
    sphere sphere_six(4, 1, -4.5, 2, 0, 0, 0);
    sphere sphere_seven(8, 4, -7.5, 2, 0, 0, 0);
    sphere sphere_eight(8, 4, -4.5, 2, 0, 0, 0);
    sphere sphere_nine(8, 1, -7.5, 2, 0, 0, 0);
    sphere sphere_ten(8, 1, -4.5, 2, 0, 0, 0);
    difference_of_objects box_sphere_one(&box_three, &sphere_three);
    difference_of_objects box_sphere_two(&box_sphere_one, &sphere_four);
    difference_of_objects box_sphere_three(&box_sphere_two, &sphere_five);
    difference_of_objects box_sphere_four(&box_sphere_three, &sphere_six);
    difference_of_objects box_sphere_five(&box_sphere_four, &sphere_seven);
    difference_of_objects box_sphere_six(&box_sphere_five, &sphere_eight);
    difference_of_objects box_sphere_seven(&box_sphere_six, &sphere_nine);
    difference_of_objects box_sphere_eight(&box_sphere_seven, &sphere_ten);

    sphere sphere_eleven(8, 4, 8, 2.5, 210, 100, 50);
    box box_four(8, 4, 8, 2, 2, 2, 0, 0, 0);
    intersection_of_objects sphere_box_one(&sphere_eleven, &box_four);

    box box_five(6, -2, 4, 2, 1, 1, 100, 150, 10);
    box box_six(6, -2, 4, 1, 2, 1, 0, 0, 0);
    box box_seven(6, -2, 4, 1, 1, 2, 0, 0, 0);
    box box_eight(6, -2, 4, 1, 2, 1, 0, 0, 0);
    union_of_objects box_box_one(&box_five, &box_six);
    union_of_objects box_box_two(&box_box_one, &box_seven);
    union_of_objects box_box_three(&box_box_two, &box_eight);
    std::vector<object_interface*> objects = {&box_one, &box_two, &sphere_one, &sphere_two,
                                              &box_sphere_eight, &sphere_box_one, &box_box_three};
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