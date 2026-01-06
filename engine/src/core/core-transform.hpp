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
    // TYPES
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

    struct transform_table {
        u32 count;
        struct {
            transform_id* id;
            f32*          x;
            f32*          y;
            f32*          z;        
        } data;

        
        inline void
        validate(
            void) {

            bool is_valid = true; 
            is_valid &= (this->data.id != NULL);
            is_valid &= (this->data.x  != NULL);
            is_valid &= (this->data.y  != NULL);
            is_valid &= (this->data.z  != NULL);
            assert(is_valid);
        }
    };

    struct translation_table : transform_table {

        inline void
        read(
            const u32     in_index,
            transform_id& out_id,
            translation&  out_translation) {

            assert(in_index < this->count);
            out_id            = this->data.id [in_index];
            out_translation.x = this->data.x  [in_index];
            out_translation.y = this->data.y  [in_index];
            out_translation.z = this->data.z  [in_index];
        }
        
        inline void
        write(
            const u32     index,
            translation&  translation) {

            assert(index < this->count);
            this->data.x [index] = translation.x;
            this->data.y [index] = translation.y;
            this->data.z [index] = translation.z;
        }
    };

    struct scale_table : transform_table {
        
        inline void
        read(
            const u32     in_index,
            transform_id& out_id,
            scale&        out_scale) {

            assert(in_index < this->count);
            out_id      = this->data.id [in_index];
            out_scale.x = this->data.x  [in_index];
            out_scale.y = this->data.y  [in_index];
            out_scale.z = this->data.z  [in_index];
        }
        
        inline void
        write(
            const u32 index,
            scale&    scale) {

            assert(index < this->count);
            this->data.x [index] = scale.x;
            this->data.y [index] = scale.y;
            this->data.z [index] = scale.z;
        }
    };
    
    struct rotation_table : transform_table {
                
        inline void
        read(
            const u32     in_index,
            transform_id& out_id,
            rotation&     out_rotation) {

            assert(in_index < this->count);
            out_id         = this->data.id [in_index];
            out_rotation.x = this->data.x  [in_index];
            out_rotation.y = this->data.y  [in_index];
            out_rotation.z = this->data.z  [in_index];
        }
        
        inline void
        write(
            const u32 index,
            rotation& rotation) {

            assert(index < this->count);
            this->data.x [index] = rotation.x;
            this->data.y [index] = rotation.y;
            this->data.z [index] = rotation.z;
        }
    };
};

#endif //CORE_TRANSFORM_HPP