#include <sys/param.h>
#include <cmath>
#include <vector>
#include <cfloat>
#include "object_interface.cpp"

inline void write_r(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void write_g(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void write_b(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void render_pixel(uint8_t* image, const int image_x, const int image_y, const int x_size,
        const float x_angle, const float y_angle, const float camera_x, const float camera_y, const float camera_z,
        const float far_clip, object_interface** object_array, int object_array_length);
inline float deg2rad (float degrees);
inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2);

//very small number
constexpr float epsilon = 0.001;

void render(const int image_x_size, const int image_y_size, uint8_t* image, object_interface** object_array, int object_array_length)
{
    const float image_x_fov = deg2rad(90);
    const float image_y_fov = deg2rad(90);

    constexpr float far_clip = 1000;

    constexpr float camera_x_pos = 0;
    constexpr float camera_y_pos = 0;
    constexpr float camera_z_pos = 0;

    const float camera_x_view_angle = deg2rad(0);
    const float camera_y_view_angle = deg2rad(0);

    for (int y = 0; y < image_y_size; ++y) {
        for (int x = 0; x < image_x_size; ++x) {
            float x_angle = camera_x_view_angle - (image_x_fov / 2) + (image_x_fov / image_x_size) * x;
            float y_angle = camera_y_view_angle - (image_y_fov / 2) + (image_y_fov / image_y_size) * y;
            render_pixel(image, x, y, image_x_size, x_angle, y_angle, camera_x_pos, camera_y_pos, camera_z_pos,
                    far_clip, object_array, object_array_length);
        }
    }
}

void render_pixel(uint8_t* image, const int image_x, const int image_y, const int x_size,
        const float x_angle, const float y_angle, const float camera_x, const float camera_y, const float camera_z,
        const float far_clip, object_interface** object_array, int object_array_length)
{
    const float direction_x = cos(x_angle) * cos(y_angle);
    const float direction_z = sin(x_angle) * cos(y_angle);
    const float direction_y = sin(y_angle);
    float x = camera_x;
    float y = camera_y;
    float z = camera_z;
    float smallest_distance = FLT_MAX;
    int nearest_sphere;

    for (int i = 0; i < object_array_length; ++i) {
        float distance = object_array[i]->distance_to_surface(x,y,z);

        if(distance < smallest_distance){
            smallest_distance = distance;
            nearest_sphere = i;
        }
    }

    while (smallest_distance > epsilon && distance_between(camera_x, camera_y, camera_z, x, y, z) < far_clip)
    {
        x += smallest_distance * direction_x;
        y += smallest_distance * direction_y;
        z += smallest_distance * direction_z;

        smallest_distance = FLT_MAX;

        for (int i = 0; i < object_array_length; ++i) {
            float distance = object_array[i]->distance_to_surface(x,y,z);

            if(distance < smallest_distance){
                smallest_distance = distance;
                nearest_sphere = i;
            }
        }
    }

    if (smallest_distance > epsilon)
    {
        //reached far clip, make pixel black
        write_r(image, image_x, image_y, x_size, 0);
        write_g(image, image_x, image_y, x_size, 0);
        write_b(image, image_x, image_y, x_size, 0);
    }
    else
    {
        //hit object, make pixel the color of the object

        write_r(image, image_x, image_y, x_size, object_array[nearest_sphere]->get_color_r());
        write_g(image, image_x, image_y, x_size, object_array[nearest_sphere]->get_color_g());
        write_b(image, image_x, image_y, x_size, object_array[nearest_sphere]->get_color_b());
    }
}

inline void write_r(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value)
{
    image[3*(image_y*x_size+image_x)+0] = value;
}

inline void write_g(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value)
{
    image[3*(image_y*x_size+image_x)+1] = value;
}

inline void write_b(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value)
{
    image[3*(image_y*x_size+image_x)+2] = value;
}

inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrt(
            pow(x1 - x2, 2)
            + pow(y1 - y2, 2)
            + pow(z1 - z2, 2));
}

inline float deg2rad(float degrees) {
    static const double pi_on_180 = 4.0 * atan (1.0) / 180.0;
    return degrees * pi_on_180;
}


