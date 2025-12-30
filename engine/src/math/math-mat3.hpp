#ifndef MATH_MAT3_HPP
#define MATH_MAT3_HPP

#include "ifb-engine.hpp"
#include "math-types.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // MATRIX 3X3
    //-------------------------------------------------------------------



    inline void mat3_identity  (mat3& m);
    inline void mat3_transpose (mat3& m);
    inline void mat3_a_mul_b   (const mat3& in_a, const mat3& in_b, mat3& out_a_mul_b);

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    inline void
    mat3_identity(
        mat3& m) {

        memset((void*)&m, 0, sizeof(mat3));

        m.r0c0 = 1;
        m.r1c1 = 1;
        m.r2c2 = 1;
    }

    inline void
    mat3_transpose(
        mat3& m) {

        
    }

    inline void
    mat3_a_mul_b(
        const mat3& in_a,
        const mat3& in_b,
        mat3&       out_a_mul_b) {

        out_a_mul_b.r0c0 = (in_a.r0c0 * in_b.r0c0) + (in_a.r0c1 * in_b.r1c0) + (in_a.r0c2 * in_b.r2c0);
        out_a_mul_b.r0c1 = (in_a.r0c0 * in_b.r0c1) + (in_a.r0c1 * in_b.r1c1) + (in_a.r0c2 * in_b.r2c1);
        out_a_mul_b.r0c2 = (in_a.r0c0 * in_b.r0c2) + (in_a.r0c1 * in_b.r1c2) + (in_a.r0c2 * in_b.r2c2);
        out_a_mul_b.r1c0 = (in_a.r1c0 * in_b.r0c0) + (in_a.r1c1 * in_b.r1c0) + (in_a.r1c2 * in_b.r2c0);
        out_a_mul_b.r1c1 = (in_a.r1c0 * in_b.r0c1) + (in_a.r1c1 * in_b.r1c1) + (in_a.r1c2 * in_b.r2c1);
        out_a_mul_b.r1c2 = (in_a.r1c0 * in_b.r0c2) + (in_a.r1c1 * in_b.r1c2) + (in_a.r1c2 * in_b.r2c2);
        out_a_mul_b.r2c0 = (in_a.r2c0 * in_b.r0c0) + (in_a.r2c1 * in_b.r1c0) + (in_a.r2c2 * in_b.r2c0);
        out_a_mul_b.r2c1 = (in_a.r2c0 * in_b.r0c1) + (in_a.r2c1 * in_b.r1c1) + (in_a.r2c2 * in_b.r2c1);
        out_a_mul_b.r2c2 = (in_a.r2c0 * in_b.r0c2) + (in_a.r2c1 * in_b.r1c2) + (in_a.r2c2 * in_b.r2c2);
    }

    inline void
    mat3_mul_vec3(
        const mat3& 
    ) {

    }
};

#endif //MATH_MAT3_HPP

// FM Hutchenson