#include <sys/param.h>
#include <cmath>
#include <vector>
#include <cfloat>
#include "object_interface.cpp"
#include "light.cpp"

struct vec3
{
    float x;
    float y;
    float z;

    inline vec3 operator+(vec3 b) const {
        return vec3(x+b.x, y+b.y, z+b.z);
    }

    inline const vec3 operator-(vec3 b) const {
        return vec3(x-b.x, y-b.y, z-b.z);
    }

    inline vec3 operator*(float s) const {
        return vec3(x*s, y*s, z*s);
    }
    inline vec3 operator/(float s) const {
        return vec3(x/s, y/s, z/s);
    }

    inline vec3 operator*(vec3 b) const {
        return vec3(x*b.x, y*b.y, z*b.z);
    }

    vec3(float x1, float y1, float z1) {
        x = x1;
        y = y1;
        z = z1;
    }
};

inline void write_r(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void write_g(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void write_b(uint8_t* image, const int image_x, const int image_y, const int x_size, const uint8_t value);
inline void render_pixel(uint8_t* image, const int image_x, const int image_y, const int x_size,
        const float x_angle, const float y_angle, const float camera_x, const float camera_y, const float camera_z,
        const float far_clip, object_interface** objects, int objects_length);
inline float deg2rad (float degrees);
inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2);
float scene_sdf(object_interface *const *objects, int objects_length, vec3 position, int &nearest_object);
vec3 estimate_normal(object_interface *const *objects, int objects_length, vec3 position);
vec3 phong_illumination(vec3 ambient_color, vec3 diffuse_color, vec3 specular_color, float alpha,
                        vec3 position, vec3 camera_position, object_interface *const *objects, int objects_length);

//very small number
constexpr float epsilon = 0.0001;

void render(const int image_x_size, const int image_y_size, uint8_t* image, object_interface** objects, int objects_length)
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
                    far_clip, objects, objects_length);
        }
    }
}

void render_pixel(uint8_t* image, const int image_x, const int image_y, const int x_size,
        const float x_angle, const float y_angle, const float camera_x, const float camera_y, const float camera_z,
        const float far_clip, object_interface** objects, int objects_length)
{
    const vec3 ambient_color = vec3(0.2,0.2,0.2);
    const vec3 diffuse_color = vec3(.4,.4,.4);
    const vec3 specular_color = vec3(.4,.4,.4);
    const float direction_x = cos(x_angle) * cos(y_angle);
    const float direction_z = sin(x_angle) * cos(y_angle);
    const float direction_y = sin(y_angle);
    const vec3 direction = vec3(direction_x, direction_y, direction_z);
    vec3 position = vec3(camera_x,camera_y,camera_z);

    int nearest_object;
    float smallest_distance = scene_sdf(objects, objects_length, position, nearest_object);

    while (smallest_distance > epsilon && distance_between(camera_x, camera_y, camera_z, position.x, position.y, position.z) < far_clip)
    {
        position = position + direction * smallest_distance;

        smallest_distance = scene_sdf(objects, objects_length, position, nearest_object);
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
        vec3 light = phong_illumination(ambient_color, diffuse_color, specular_color, 5, position,
                vec3(camera_x, camera_y, camera_z), objects, objects_length);
        vec3 color = vec3(objects[nearest_object]->get_color_r(), objects[nearest_object]->get_color_g(),
                objects[nearest_object]->get_color_b());
        color = color / 255.f;
        vec3 lit_color = color * light;

        write_r(image, image_x, image_y, x_size, lit_color.x * 255);
        write_g(image, image_x, image_y, x_size, lit_color.y * 255);
        write_b(image, image_x, image_y, x_size, lit_color.z * 255);
    }
}

float length(vec3 input)
{
    return sqrt(pow(input.x,2)+pow(input.y,2)+pow(input.z,2));
}

vec3 normalize(vec3 input)
{
    float input_length = length(input);
    return input/input_length;
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

float scene_sdf(object_interface *const *objects, int objects_length, vec3 position, int &nearest_object) {
    float smallest_distance = FLT_MAX;
    for (int i = 0; i < objects_length; ++i) {
        float distance = objects[i]->distance_to_surface(position.x,position.y,position.z);

        if(distance < smallest_distance){
            smallest_distance = distance;
            nearest_object = i;
        }
    }
    return smallest_distance;
}

vec3 estimate_normal(object_interface *const *objects, int objects_length, vec3 position) {
    int throwaway;
    return normalize(vec3(
            scene_sdf(objects,objects_length,vec3(position.x + epsilon, position.y, position.z), throwaway)
            - scene_sdf(objects,objects_length,vec3(position.x - epsilon, position.y, position.z), throwaway),
            scene_sdf(objects,objects_length,vec3(position.x, position.y + epsilon, position.z), throwaway)
            - scene_sdf(objects,objects_length,vec3(position.x, position.y - epsilon, position.z), throwaway),
            scene_sdf(objects,objects_length,vec3(position.x, position.y, position.z  + epsilon), throwaway)
            - scene_sdf(objects,objects_length,vec3(position.x, position.y, position.z - epsilon), throwaway)
    ));
}

float dot(vec3 a, vec3 b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3 reflect(vec3 i, vec3 n){
    return i - n * 2.0 * dot(n, i);
}

float clamp(float n, float lower, float upper){
    return std::max(lower, std::min(n, upper));
}

/**
 *
 * @param diffuse_color: diffuse color
 * @param specular_color: specular color
 * @param alpha: shininess coefficient
 * @param position: position of point being lit
 * @param camera_position: position of the camera
 * @param light_pos: position of the light
 * @param light_intensity: color/intensity of the light
 * @return
 */
vec3 phong_contrib_for_light(vec3 diffuse_color, vec3 specular_color, float alpha, vec3 position,
        vec3 camera_position, vec3 light_pos, vec3 light_intensity, object_interface *const *objects, int objects_length){
    vec3 normal = estimate_normal(objects, objects_length, position);
    vec3 object_light_direction = normalize(light_pos - position);
    vec3 camera_object_direction = normalize(camera_position - position);
    vec3 reflection_direction = normalize(reflect(object_light_direction * -1, normal));
    float dot_o_n = clamp(dot(object_light_direction, normal), 0, 1);
    float dot_r_c = dot(reflection_direction, camera_object_direction);

    if(dot_o_n < 0){
        return vec3(0, 0, 0);
    }

    if(dot_r_c < 0){
        return light_intensity * (diffuse_color * dot_o_n);
    }

    return light_intensity * (diffuse_color * dot_o_n + specular_color * pow(dot_r_c, alpha));
}

vec3 phong_illumination(vec3 ambient_color, vec3 diffuse_color, vec3 specular_color, float alpha, vec3 position,
                        vec3 camera_position, object_interface *const *objects, int objects_length) {
    const vec3 ambient_light = vec3(1, 1, 1) * 0.5f;
    vec3 color = ambient_light * ambient_color;
    light light_one(3, 3, 3, .7, .7, .7);
    light light_two(2, -10, -5, 0.9, 0.9, 0.9);

    color = color + phong_contrib_for_light(diffuse_color, specular_color, alpha, position, camera_position,
                                            vec3(light_one.x, light_one.y, light_one.z), vec3(light_one.r, light_one.g, light_one.b),
                                            objects, objects_length);
    color = color + phong_contrib_for_light(diffuse_color, specular_color, alpha, position, camera_position,
                                            vec3(light_two.x, light_two.y, light_two.z), vec3(light_two.r, light_two.g, light_two.b),
                                            objects, objects_length);

    return vec3(clamp(color.x,0.,1.),clamp(color.y,0.,1.),
            clamp(color.z,0.,1.));
}


