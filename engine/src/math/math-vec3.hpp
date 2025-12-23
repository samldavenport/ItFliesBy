#ifndef IFB_ENGINE_MATH_VEC3_HPP
#define IFB_ENGINE_MATH_VEC3_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // VECTOR 3D
    //-------------------------------------------------------------------

    struct vec3 {
        union {
            struct {
                f32 x;
                f32 y;
                f32 z;
            };
            f32 buffer[3];
        };
    };
    
    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_API_INLINE void vec3_normalize  (vec3& v);
    IFB_ENG_API_INLINE void vec3_magnitude  (const vec3& in_v,        f32&  out_m);
    IFB_ENG_API_INLINE void vec3_scalar_mul (const vec3& in_v,  const f32&  in_s,  vec3& out_v_mul_s);
    IFB_ENG_API_INLINE void vec3_scalar_div (const vec3& in_v,  const f32&  in_s,  vec3& out_v_div_s);
    IFB_ENG_API_INLINE void vec3_a_add_b    (const vec3& in_va, const vec3& in_vb, vec3& out_va_add_vb);
    IFB_ENG_API_INLINE void vec3_a_sub_b    (const vec3& in_va, const vec3& in_vb, vec3& out_va_sub_vb);
    IFB_ENG_API_INLINE void vec3_a_dot_b    (const vec3& in_va, const vec3& in_vb, vec3& out_va_dot_vb);
    IFB_ENG_API_INLINE void vec3_a_cross_b  (const vec3& in_va, const vec3& in_vb, vec3& out_va_cross_vb);

    //-------------------------------------------------------------------
    // INLINE DEFINITIONS
    //-------------------------------------------------------------------

    IFB_ENG_API_INLINE void
    vec3_normalize(
        vec3& v) {

        assert(v.x != 0 || v.y != 0 || v.z != 0);

        const f32 normal_factor = 1.0f / sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
        v.x *= normal_factor;
        v.y *= normal_factor;
        v.z *= normal_factor;
    }

    IFB_ENG_API_INLINE void
    vec3_magnitude(
        const vec3& in_v,
        f32&        out_m) {

        assert(v.x != 0 || v.y != 0 || v.z != 0);
        out_m = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    IFB_ENG_API_INLINE void
    vec3_scalar_mul(
        const vec3& in_v,
        const f32&  in_s,
        vec3&       out_v_mul_s) {

        out_v_mul_s.x = (in_v.x * in_s);
        out_v_mul_s.y = (in_v.y * in_s);
    }

    IFB_ENG_API_INLINE void
    vec3_scalar_div(
        const vec3& in_v,
        const f32&  in_s,
        vec3&       out_v_div_s) {

        assert(in_s != 0);

        out_v_div_s.x = (in_v.x / in_s);
        out_v_div_s.x = (in_v.y / in_s);
    }

    IFB_ENG_API_INLINE void
    vec3_a_add_b(
        const vec3& in_va,
        const vec3& in_vb,
        vec3&       out_va_add_vb) {

        out_va_add_vb.x = (in_va.x + in_vb.x);
        out_va_add_vb.y = (in_va.y + in_vb.y);
    }

    IFB_ENG_API_INLINE void
    vec3_a_sub_b(
        const vec3& in_va,
        const vec3& in_vb,
        vec3&       out_va_sub_vb) {

        out_va_add_vb.x = (in_va.x - in_vb.x);
        out_va_add_vb.y = (in_va.y - in_vb.y);
    }

    IFB_ENG_API_INLINE void
    vec3_a_dot_b(
        const vec3& in_va,
        const vec3& in_vb,
        f32&        out_va_dot_vb) {

        out_va_dot_vb = ((in_va.x * in_vb.x) + (in_va.y * in_vb.y));
    }
};

#endif //IFB_ENGINE_MATH_VEC3_HPP