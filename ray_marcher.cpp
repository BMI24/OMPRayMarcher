#include <cmath>
#include <vector>
#include <cfloat>
#include "object_interface.hpp"
#include "light.h"
#include <queue>


struct vec3
{
    float x;
    float y;
    float z;

    inline vec3 operator+(const vec3& b) const {
        return {x+b.x, y+b.y, z+b.z};
    }

    inline vec3 operator-(const vec3& b) const {
        return {x-b.x, y-b.y, z-b.z};
    }

    inline vec3 operator*(const float s) const {
        return {x*s, y*s, z*s};
    }
    inline vec3 operator/(const float s) const {
        return {x/s, y/s, z/s};
    }

    inline vec3 operator*(const vec3& b) const {
        return {x*b.x, y*b.y, z*b.z};
    }

    vec3(float x1, float y1, float z1) {
        x = x1;
        y = y1;
        z = z1;
    }

    inline float length() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
};

struct mat4x4
{
    float* matrix;

    mat4x4()
    {
        matrix = new float[16]();
    }

    ~mat4x4()
    {
        delete[] matrix;
    }

    inline mat4x4 operator*(const mat4x4& b) const {
        mat4x4 result;
        for(int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.matrix[i * 4 + j] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.matrix[i * 4 + j] += matrix[i * 4 + k] * b.matrix[k * 4 + j];
                }
            }
        }
        return result;
    }

    inline vec3 operator*(const vec3& b) const{
        constexpr float b4 = 1;
        return {
                b.x*matrix[0]+b.y*matrix[1]+b.z*matrix[2]+b4*matrix[3],
                b.x*matrix[4]+b.y*matrix[5]+b.z*matrix[6]+b4*matrix[7],
                b.x*matrix[8]+b.y*matrix[9]+b.z*matrix[10]+b4*matrix[11]};
    }
};

mat4x4 generate_mat_transl(float translation_x, float translation_y, float translation_z)
{
    mat4x4 scale_mat;
    scale_mat.matrix[0] = 1;
    scale_mat.matrix[3] = translation_x;
    scale_mat.matrix[5] = 1;
    scale_mat.matrix[7] = translation_y;
    scale_mat.matrix[10] = 1;
    scale_mat.matrix[11] = translation_z;
    scale_mat.matrix[15] = 1;

    return scale_mat;
}

mat4x4 generate_mat_scale(float scale_x, float scale_y, float scale_z)
{
    mat4x4 scale_mat;
    scale_mat.matrix[0] = scale_x;
    scale_mat.matrix[5] = scale_y;
    scale_mat.matrix[10] = scale_z;
    scale_mat.matrix[15] = 1;
    return scale_mat;
}

mat4x4 generate_mat_rot_x(float angle)
{
    mat4x4 rot_mat;
    rot_mat.matrix[0] = 1;
    rot_mat.matrix[5] = cosf(angle);
    rot_mat.matrix[6] = -sinf(angle);
    rot_mat.matrix[9] = sinf(angle);
    rot_mat.matrix[10] = cosf(angle);
    rot_mat.matrix[15] = 1;
    return rot_mat;
}

mat4x4 generate_mat_rot_y(float angle)
{
    mat4x4 rot_mat;
    rot_mat.matrix[0] = cosf(angle);
    rot_mat.matrix[2] = sinf(angle);
    rot_mat.matrix[5] = 1;
    rot_mat.matrix[8] = -sinf(angle);
    rot_mat.matrix[10] = cosf(angle);
    rot_mat.matrix[15] = 1;
    return rot_mat;
}

mat4x4 generate_mat_rot_z(float angle)
{
    mat4x4 rot_mat;
    rot_mat.matrix[0] = cosf(angle);
    rot_mat.matrix[1] = -sinf(angle);
    rot_mat.matrix[4] = sinf(angle);
    rot_mat.matrix[5] = cosf(angle);
    rot_mat.matrix[10] = 1;
    rot_mat.matrix[15] = 1;
    return rot_mat;
}

inline void write_r(uint8_t* image, int image_x, int image_y, int x_size, uint8_t value);
inline void write_g(uint8_t* image, int image_x, int image_y, int x_size, uint8_t value);
inline void write_b(uint8_t* image, int image_x, int image_y, int x_size, uint8_t value);
inline void render_pixel(uint8_t* image, int image_x, int image_y, int x_size,
        vec3& direction, float camera_x, float camera_y, float camera_z, float far_clip,
        object_interface** objects, int objects_length, light** lights, int lights_length);
inline float deg2rad (float degrees);
inline float distance_between(float x1, float y1, float z1, float x2, float y2, float z2);
float scene_sdf(object_interface *const *objects, int objects_length, const vec3& position, int &nearest_object);
vec3 estimate_normal(object_interface *const *objects, int objects_length, const vec3& position);
vec3 phong_illumination(const vec3& ambient_color, const vec3& diffuse_color, const vec3& specular_color, float alpha,
        const vec3& position, const vec3& camera_position, object_interface *const *objects, int objects_length,
        int hit_object_index, light *const *lights, int lights_length);
vec3 normalize(const vec3& input);
float scene_sdf_optimized(object_interface *const *objects, int objects_length, const vec3& position, int &nearest_object, float* known_distances);

//very small number
constexpr float epsilon = 0.001;

void render(const int image_x_size, const int image_y_size, uint8_t* image, object_interface** objects,
        int objects_length, light** lights, int lights_length, float camera_x_pos, float camera_y_pos,
        float camera_z_pos, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y,
        float scale_z, float fov, float far_clip)
{
    rot_x = deg2rad(rot_x);
    rot_y = deg2rad(rot_y);
    rot_z = deg2rad(rot_z);

    mat4x4 camera_to_world = generate_mat_transl(camera_x_pos, camera_y_pos, camera_z_pos) *
            generate_mat_scale(scale_x, scale_y, scale_z) *
            generate_mat_rot_x(rot_x) * generate_mat_rot_y(rot_y) * generate_mat_rot_z(rot_z);

    float aspect_ratio = (float)image_x_size / (float) image_y_size;
    float fov_scale = tanf(deg2rad(fov * .5f));
    vec3 origin = camera_to_world * vec3(0,0,0);

#pragma omp parallel for collapse(2)
    for (int j = 0; j < image_y_size; ++j) {
        for (int i = 0; i < image_x_size; ++i) {
            float x = (2 * ((float)i+.5f)/ (float)image_x_size - 1.f) * aspect_ratio * fov_scale;
            float y = (1 - 2 * ((float)j+.5f) / (float)image_y_size) * fov_scale;
            vec3 dir = camera_to_world * vec3(x,y,-1) - origin;
            dir = normalize(dir);
            render_pixel(image, i, j, image_x_size, dir, camera_x_pos, camera_y_pos, camera_z_pos,
                    far_clip, objects, objects_length, lights, lights_length);
        }
    }
}

void render_pixel(uint8_t* image, int image_x, int image_y, int x_size,
                  vec3& direction, float camera_x, float camera_y, float camera_z, float far_clip,
                  object_interface** objects, int objects_length, light** lights, int lights_length)
{
    const vec3 ambient_color = vec3(.1,.1,.1);
    const vec3 diffuse_color = vec3(.4,.4,.4);
    const vec3 specular_color = vec3(.4,.4,.4);

    vec3 position = vec3(camera_x,camera_y,camera_z);
    float known_distances[objects_length];

    int nearest_object;
    float smallest_distance = scene_sdf_optimized(objects, objects_length, position, nearest_object, known_distances);

    while (smallest_distance > epsilon && distance_between(camera_x, camera_y, camera_z, position.x, position.y, position.z) < far_clip)
    {
        position = position + direction * smallest_distance;

        smallest_distance = scene_sdf_optimized(objects, objects_length, position, nearest_object, known_distances);
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
                vec3(camera_x, camera_y, camera_z), objects, objects_length, nearest_object,
                lights, lights_length);
        uint32_t packed_color = objects[nearest_object]->get_color(position.x, position.y, position.z);
        vec3 color = vec3(packed_color >> 24u, float((packed_color >> 16u)&0xffu), float((packed_color>>8u)&0xffu));
        color = color / 255.f;
        vec3 lit_color = color * light;

        write_r(image, image_x, image_y, x_size, lit_color.x * 255);
        write_g(image, image_x, image_y, x_size, lit_color.y * 255);
        write_b(image, image_x, image_y, x_size, lit_color.z * 255);
    }
}

vec3 normalize(const vec3& input)
{
    float input_length = input.length();
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
    float xdiff = x1 - x2;
    float ydiff = y1 - y2;
    float zdiff = z1 - z2;
    return std::sqrt(xdiff*xdiff+ydiff*ydiff+zdiff*zdiff);
}

inline float deg2rad(float degrees) {
    static const float pi_on_180 = 4.f * atanf(1.0) / 180.f;
    return degrees * pi_on_180;
}

float scene_sdf_optimized(object_interface *const *objects, int objects_length, const vec3& position, int &nearest_object, float* known_distances) {
    float smallest_distance = FLT_MAX;
    for (int i = 0; i < objects_length; ++i) {
        float distance;
        if (known_distances[i] <= epsilon) {
            distance = objects[i]->distance_to_surface(position.x, position.y, position.z);
            known_distances[i] = distance;
        }
        else {
            distance = known_distances[i];
        }

        if(distance < smallest_distance){
            smallest_distance = distance;
            nearest_object = i;
        }
    }
    for (int i = 0; i < objects_length; ++i) {
        known_distances[i] -= smallest_distance;
    }
    return smallest_distance;
}

float scene_sdf_optimized_exact(object_interface *const *objects, int objects_length, const vec3& position, int &nearest_object, float* known_distances) {
    struct distance_with_index
    {
        float distance;
        int index;
        distance_with_index(float distance, int index)
        {
            this->distance = distance;
            this->index = index;
        }
    };

    auto cmp = [](distance_with_index& left, distance_with_index& right) { return left.distance > right.distance; };
    std::priority_queue<distance_with_index, std::vector<distance_with_index>, decltype(cmp)> pqueue(cmp);
    for (int i = 0; i < objects_length; ++i) {
        pqueue.push(distance_with_index(known_distances[i], i));
    }

    float min_distance;
    bool new_min_distance_found;
    do{
        min_distance = pqueue.top().distance;
        nearest_object = pqueue.top().index;
        float new_min_distance = objects[nearest_object]->distance_to_surface(position.x, position.y, position.z);
        if (std::abs(new_min_distance - min_distance) < 0.1f * epsilon)
        {
            new_min_distance_found = false;
        }
        else
        {
            known_distances[nearest_object] = new_min_distance;
            pqueue.pop();
            pqueue.push(distance_with_index(new_min_distance, nearest_object));
            new_min_distance_found = true;
        }
    }
    while (new_min_distance_found);
    return min_distance;
}

float scene_sdf(object_interface *const *objects, int objects_length, const vec3& position, int &nearest_object) {
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

vec3 estimate_normal(object_interface *const *objects, int objects_length, const vec3& position) {
    int discard;
    return normalize(vec3(
            scene_sdf(objects,objects_length,vec3(position.x + epsilon, position.y, position.z), discard)
            - scene_sdf(objects,objects_length,vec3(position.x - epsilon, position.y, position.z), discard),
            scene_sdf(objects,objects_length,vec3(position.x, position.y + epsilon, position.z), discard)
            - scene_sdf(objects,objects_length,vec3(position.x, position.y - epsilon, position.z), discard),
            scene_sdf(objects,objects_length,vec3(position.x, position.y, position.z  + epsilon), discard)
            - scene_sdf(objects,objects_length,vec3(position.x, position.y, position.z - epsilon), discard)
    ));
}

float dot(const vec3& a, const vec3& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3 reflect(const vec3& i, const vec3& n){
    return i - n * 2.0 * dot(n, i);
}

float clamp(float n, float lower, float upper) {
    return std::fmax(lower, std::fmin(n, upper));
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
vec3 phong_contrib_for_light(const vec3& diffuse_color, const vec3& specular_color, float alpha, const vec3& position,
        const vec3& camera_position, const vec3& light_pos, const vec3& light_intensity,
        object_interface *const *objects, int objects_length){
    vec3 normal = estimate_normal(objects, objects_length, position);
    vec3 object_light_direction = normalize(light_pos - position);
    vec3 camera_object_direction = normalize(camera_position - position);
    vec3 opposite_light_direction = object_light_direction * -1.f;
    vec3 reflection_direction = normalize(reflect(opposite_light_direction, normal));
    float dot_o_n = clamp(dot(object_light_direction, normal), 0, 1);
    float dot_r_c = dot(reflection_direction, camera_object_direction);

    if(dot_o_n < 0){
        return {0, 0, 0};
    }

    if(dot_r_c < 0){
        return light_intensity * (diffuse_color * dot_o_n);
    }

    return light_intensity * (diffuse_color * dot_o_n + specular_color * std::pow(dot_r_c, alpha));
}

float light_visibility(object_interface *const *objects, int objects_length, const vec3& light_position,
        const vec3& start_position)
{
    vec3 direction = normalize(light_position-start_position);
    const float start_dist = epsilon * 10;
    float visibility = 1.f;
    float hardness = .8f;
    float max_dist = (light_position-start_position).length();
    int discard;
    for(float curr_dist = start_dist; curr_dist < max_dist;)
    {
        //TODO: if soft shadows are disabled, we could use scene_sdf_optimized here (nearly halfed my runtime)
        float min_dist = scene_sdf(objects, objects_length, start_position + (direction * curr_dist), discard);
        if (min_dist < epsilon)
            return 0.f;

        visibility = std::fmin(visibility, .5f + .5f * min_dist / (hardness * curr_dist));
        if(visibility < epsilon)
            return 0.f;
        curr_dist += min_dist;
    }
    return visibility * visibility * (3.f - 2.f * visibility); // smoothstep
}

vec3 phong_illumination(const vec3& ambient_color, const vec3& diffuse_color, const vec3& specular_color, float alpha,
                        const vec3& position, const vec3& camera_position, object_interface *const *objects, int objects_length,
                        int, light *const *lights, int lights_length) {
    const vec3 ambient_light = vec3(1, 1, 1) * 0.5f;
    vec3 color = ambient_light * ambient_color;

    for (int i = 0; i < lights_length; ++i) {
        float visibility = light_visibility(objects,objects_length,
                vec3(lights[i]->x, lights[i]->y, lights[i]->z), position);
        if (visibility < epsilon)
            continue;
        color = color + phong_contrib_for_light(diffuse_color, specular_color, alpha, position, camera_position,
                                                vec3(lights[i]->x, lights[i]->y, lights[i]->z),
                                                vec3(lights[i]->r, lights[i]->g, lights[i]->b),
                                                objects, objects_length)
                                                        * visibility;
    }

    return {clamp(color.x,0.f,1.f),
            clamp(color.y,0.f,1.f),
            clamp(color.z,0.f,1.f)};
}


