#ifndef CORE_TRANSFORM_HPP
#define CORE_TRANSFORM_HPP

#include "ifb-engine.hpp"
#include "core-id.hpp"
#include "math.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using  transform_id = id;

    struct transform;
    struct translation;
    struct scale;
    struct rotation;
    struct transform_table;
    struct translation_table;
    struct scale_table;
    struct rotation_table;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct translation  : vec3 { };
    struct scale        : vec3 { };
    struct rotation     : vec3 { };

    struct transform {
        transform_id id;
        translation  translation;
        scale        scale;
        rotation     rotation;        
    };

    struct transform_table_serialized {
        transform_data_table* next;
        transform_data_table* prev;
        u32 count;
        struct {
            transform_id* id;
            translation*  translation;
            scale*        scale;
            rotation*     rotation;
        } data;
        
        inline void
        validate(
            void) {

            bool is_valid = true; 
            is_valid &= (this->data.id          != NULL);
            is_valid &= (this->data.translation != NULL);
            is_valid &= (this->data.scale       != NULL);
            is_valid &= (this->data.rotation    != NULL);
            assert(is_valid);
        }
    };

    struct transform_table_vectorized {
        u32 count;
        struct {
            transform_id* id;
            struct {
                f32* x;
                f32* y;
                f32* z;
            } translation;
            struct {
                f32* x;
                f32* y;
                f32* z;
            } scale;
            struct {
                f32* x;
                f32* y;
                f32* z;
            } rotation;
        } data;
    };
};

#endif //CORE_TRANSFORM_HPP