#pragma once

#include "managers.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct transform_table {
        f32* x;
        f32* y;
        f32* z;
    };

    struct transform_manager {
        sparse_index_array sparse_indexes;
        struct {
            transform_table translation;
            transform_table scale;
            transform_table rotation;
        } dense_data;
    };

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL transform_manager*
    transform_manager_init(
        const void* memory_start,
        const u32   memory_size, 
        const u32   capacity,
        const f32   max_load_p100) {

    }

    IFB_ENG_INTERNAL u32
    transform_calculate_memory_size(
        const u32 capacity,
        const f32 max_load_p100) {

    }

    IFB_ENG_INTERNAL void
    transform_manager_validate(
        transform_manager* const tm) {

    }
    
    IFB_ENG_INTERNAL u32
    transform_capacity(
        transform_manager* const tm) {

    }
    
    IFB_ENG_INTERNAL u32
    transform_count(
        transform_manager* const tm) {

    }
    
    IFB_ENG_INTERNAL u32
    transform_max_count(
        transform_manager* const tm) {

    }
    
};