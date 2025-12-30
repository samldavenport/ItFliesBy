#ifndef MATH_MAT4_HPP
#define MATH_MAT4_HPP

#include "ifb-engine.hpp"
#include "math-types.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // MATRIX 4X4
    //-------------------------------------------------------------------

    inline void mat4_identity  (mat4& m);
    inline void mat4_transpose (mat4& m);
    inline void mat4_a_mul_b   (const mat4& in_a, const mat4& in_b, mat4& out_a_mul_b);

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------
    
    inline void
    mat4_identity(
        mat4& m) {

        memset((void*)&m, 0, sizeof(mat4));

        m.r0c0 = 1;
        m.r1c1 = 1;
        m.r2c2 = 1;
        m.r3c3 = 1;
    }

    inline void
    mat4_transpose(
        mat4& m) {

        
    }

    inline void
    mat4_a_mul_b(
        const mat4& in_a,
        const mat4& in_b,
        mat4&       out_a_mul_b) {

        out_a_mul_b.r0c0 = (in_a.r0c0 * in_b.r0c0) + (in_a.r0c1 * in_b.r1c0) + (in_a.r0c2 * in_b.r2c0)+ (in_a.r0c3 * in_b.r3c0);
        out_a_mul_b.r0c1 = (in_a.r0c0 * in_b.r0c1) + (in_a.r0c1 * in_b.r1c1) + (in_a.r0c2 * in_b.r2c1)+ (in_a.r0c3 * in_b.r3c1);
        out_a_mul_b.r0c2 = (in_a.r0c0 * in_b.r0c2) + (in_a.r0c1 * in_b.r1c2) + (in_a.r0c2 * in_b.r2c2)+ (in_a.r0c3 * in_b.r3c2);
        out_a_mul_b.r0c3 = (in_a.r0c0 * in_b.r0c3) + (in_a.r0c1 * in_b.r1c3) + (in_a.r0c2 * in_b.r2c3)+ (in_a.r0c3 * in_b.r3c3);
        out_a_mul_b.r1c0 = (in_a.r1c0 * in_b.r0c0) + (in_a.r1c1 * in_b.r1c0) + (in_a.r1c2 * in_b.r2c0)+ (in_a.r1c3 * in_b.r3c0);
        out_a_mul_b.r1c1 = (in_a.r1c0 * in_b.r0c1) + (in_a.r1c1 * in_b.r1c1) + (in_a.r1c2 * in_b.r2c1)+ (in_a.r1c3 * in_b.r3c1);
        out_a_mul_b.r1c2 = (in_a.r1c0 * in_b.r0c2) + (in_a.r1c1 * in_b.r1c2) + (in_a.r1c2 * in_b.r2c2)+ (in_a.r1c3 * in_b.r3c2);
        out_a_mul_b.r1c3 = (in_a.r1c0 * in_b.r0c3) + (in_a.r1c1 * in_b.r1c3) + (in_a.r1c2 * in_b.r2c3)+ (in_a.r1c3 * in_b.r3c3);
        out_a_mul_b.r2c0 = (in_a.r2c0 * in_b.r0c0) + (in_a.r2c1 * in_b.r1c0) + (in_a.r2c2 * in_b.r2c0)+ (in_a.r2c3 * in_b.r3c0);
        out_a_mul_b.r2c1 = (in_a.r2c0 * in_b.r0c1) + (in_a.r2c1 * in_b.r1c1) + (in_a.r2c2 * in_b.r2c1)+ (in_a.r2c3 * in_b.r3c1);
        out_a_mul_b.r2c2 = (in_a.r2c0 * in_b.r0c2) + (in_a.r2c1 * in_b.r1c2) + (in_a.r2c2 * in_b.r2c2)+ (in_a.r2c3 * in_b.r3c2);
        out_a_mul_b.r2c3 = (in_a.r2c0 * in_b.r0c3) + (in_a.r2c1 * in_b.r1c3) + (in_a.r2c2 * in_b.r2c3)+ (in_a.r2c3 * in_b.r3c3);
        out_a_mul_b.r3c0 = (in_a.r2c0 * in_b.r0c0) + (in_a.r3c1 * in_b.r1c0) + (in_a.r3c2 * in_b.r2c0)+ (in_a.r3c3 * in_b.r3c0);
        out_a_mul_b.r3c1 = (in_a.r2c0 * in_b.r0c1) + (in_a.r3c1 * in_b.r1c1) + (in_a.r3c2 * in_b.r2c1)+ (in_a.r3c3 * in_b.r3c1);
        out_a_mul_b.r3c2 = (in_a.r2c0 * in_b.r0c2) + (in_a.r3c1 * in_b.r1c2) + (in_a.r3c2 * in_b.r2c2)+ (in_a.r3c3 * in_b.r3c2);
        out_a_mul_b.r3c3 = (in_a.r2c0 * in_b.r0c3) + (in_a.r3c1 * in_b.r1c3) + (in_a.r3c2 * in_b.r2c3)+ (in_a.r3c3 * in_b.r3c3);
    }
};

#endif //MATH_MAT4_HPP