#include <cmath>
#include "box.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
float box::distance_to_surface(float x2, float y2, float z2) {
    // SSE2 intrinsics used to implement vectorization
    // --> guaranteed to compile on every 64 bit architecture (quite portable)

    auto diff = _mm_sub_ps(vars.vec, _mm_setr_ps(x2, y2, z2, 0.f));

    // logical left --- right shift by one to compute abs
    auto vtmp = _mm_slli_epi32((__m128i)diff, 1);
    auto dists = (__m128)_mm_srli_epi32(vtmp, 1);

    aligned_data zero_min;
    dists = _mm_sub_ps(dists, lengths.vec);
    auto zero_max =  _mm_max_ps(dists, _mm_set1_ps(0.f));
    zero_min.vec =  _mm_min_ps(dists, _mm_set1_ps(0.f));

    aligned_data dists_mult;
    dists_mult.vec = _mm_mul_ps(zero_max, zero_max);

    auto _length = sqrtf(dists_mult.arr[0] + dists_mult.arr[1] + dists_mult.arr[2]);

    return std::fmax(zero_min.vec[0], std::fmax(zero_min.vec[1], zero_min.vec[2])) + _length;
}
#pragma clang diagnostic pop

//linear interpolation
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

uint32_t box::get_color(float, float, float) {
    return color;
}

box::box(float x, float y, float z, float x_length, float y_length, float z_length, uint32_t color){
    vars.vec = _mm_setr_ps(x, y, z, 0.f);
    lengths.vec = _mm_setr_ps(x_length, y_length, z_length, 0.f);
    this->color = color;
}