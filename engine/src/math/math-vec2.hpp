#ifndef IFB_ENGINE_MATH_VEC2_HPP
#define IFB_ENGINE_MATH_VEC2_HPP

#include "ifb-engine.hpp"
#include "core-data.hpp"
#include <math.h>

namespace ifb::eng {
    
    //-------------------------------------------------------------------
    // VECTOR 2D
    //-------------------------------------------------------------------

    struct vec2 {
        union {
            struct {
                f32 x;
                f32 y;
            };
            f32 buffer[2];
        };
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API_INLINE void vec2_normalize  (vec2& v);
    IFB_ENG_API_INLINE void vec2_magnitude  (const vec2& in_v,        f32&  out_m);
    IFB_ENG_API_INLINE void vec2_scalar_mul (const vec2& in_v,  const f32&  in_s,  vec2& out_v_mul_s);
    IFB_ENG_API_INLINE void vec2_scalar_div (const vec2& in_v,  const f32&  in_s,  vec2& out_v_div_s);
    IFB_ENG_API_INLINE void vec2_a_add_b    (const vec2& in_va, const vec2& in_vb, vec2& out_va_add_vb);
    IFB_ENG_API_INLINE void vec2_a_sub_b    (const vec2& in_va, const vec2& in_vb, vec2& out_va_sub_vb);
    IFB_ENG_API_INLINE void vec2_a_dot_b    (const vec2& in_va, const vec2& in_vb, vec2& out_va_dot_vb);

    //-------------------------------------------------------------------
    // INLINE DEFINITIONS
    //-------------------------------------------------------------------

    IFB_ENG_API_INLINE void
    vec2_normalize(
        vec2& v) {

        assert(v.x != 0 || v.y != 0);

        const f32 normal_factor = 1.0f / sqrtf((v.x * v.x) + (v.y * v.y));
        v.x *= normal_factor;
        v.y *= normal_factor;
    }

    IFB_ENG_API_INLINE void
    vec2_magnitude(
        const vec2& in_v,
        f32&        out_m) {

        assert(in_v.x != 0 || in_v.y != 0);
        out_m = sqrtf((in_v.x * in_v.x) + (in_v.y * in_v.y));
    }

    IFB_ENG_API_INLINE void
    vec2_scalar_mul(
        const vec2& in_v,
        const f32&  in_s,
        vec2&       out_v_mul_s) {

        out_v_mul_s.x = (in_v.x * in_s);
        out_v_mul_s.y = (in_v.y * in_s);
    }

    IFB_ENG_API_INLINE void
    vec2_scalar_div(
        const vec2& in_v,
        const f32&  in_s,
        vec2&       out_v_div_s) {

        assert(in_s != 0);

        out_v_div_s.x = (in_v.x / in_s);
        out_v_div_s.x = (in_v.y / in_s);
    }

    IFB_ENG_API_INLINE void
    vec2_a_add_b(
        const vec2& in_va,
        const vec2& in_vb,
        vec2&       out_va_add_vb) {

        out_va_add_vb.x = (in_va.x + in_vb.x);
        out_va_add_vb.y = (in_va.y + in_vb.y);
    }

    IFB_ENG_API_INLINE void
    vec2_a_sub_b(
        const vec2& in_va,
        const vec2& in_vb,
        vec2&       out_va_sub_vb) {

        out_va_sub_vb.x = (in_va.x - in_vb.x);
        out_va_sub_vb.y = (in_va.y - in_vb.y);
    }

    IFB_ENG_API_INLINE void
    vec2_a_dot_b(
        const vec2& in_va,
        const vec2& in_vb,
        f32&        out_va_dot_vb) {

        out_va_dot_vb = ((in_va.x * in_vb.x) + (in_va.y * in_vb.y));
    }
};

#endif //IFB_ENGINE_MATH_VEC2_HPP