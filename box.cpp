#include <cmath>
#include "box.h"

inline float length(float x1, float y1, float z1) {
    return sqrtf(
            powf(x1, 2)
            + powf(y1, 2)
            + powf(z1, 2));
}

float box::distance_to_surface(float x2, float y2, float z2) {
    float x_distance = fabsf(x-x2) - x_length;
    float y_distance = fabsf(y-y2) - y_length;
    float z_distance = fabsf(z-z2) - z_length;

    return std::fmin(std::fmax(x_distance, std::fmax(y_distance, z_distance)), 0.f)
           + length(std::fmax(x_distance, 0.f), std::fmax(y_distance,0.f), std::fmax(z_distance,0.f));
}

inline uint32_t lerp (uint32_t a, uint32_t b, float ratio)
{
    uint8_t a_r = a >> 24u;
    uint8_t a_g = a >> 16u & 0xFFu;
    uint8_t a_b = a >> 8u & 0xFFu;
    uint8_t a_a = a & 0xFFu;

    uint8_t b_r = b >> 24u;
    uint8_t b_g = b >> 16u & 0xFFu;
    uint8_t b_b = b >> 8u & 0xFFu;
    uint8_t b_a = b & 0xFFu;

    auto r_r = uint8_t(float(a_r) * (1.f-ratio) + float(b_r) * ratio);
    auto r_g = uint8_t(float(a_g) * (1.f-ratio) + float(b_g) * ratio);
    auto r_b = uint8_t(float(a_b) * (1.f-ratio) + float(b_b) * ratio);
    auto r_a = uint8_t(float(a_a) * (1.f-ratio) + float(b_a) * ratio);
    return r_r << 24u | r_g << 16u | r_b << 8u | r_a; // NOLINT(hicpp-signed-bitwise)
}

uint32_t box::get_color(float, float y2, float) {
    return color;
}

box::box(float x, float y, float z, float x_length, float y_length, float z_length, uint32_t color){
    this->x = x;
    this->y = y;
    this->z = z;
    this->x_length = x_length;
    this->y_length = y_length;
    this->z_length = z_length;
    this->color = color;
}