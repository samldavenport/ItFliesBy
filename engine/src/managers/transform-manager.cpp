#pragma once

#include "managers.hpp"
#include <sld-sparse-array.hpp>
#include <sld-stack.hpp>

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
            u32*            sparse_index;
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

        // calculate minimum required memory
        const u32 memory_size_min = transform_calculate_memory_size(capacity, max_load_p100); 

        // check args
        bool can_init = true;
        can_init &= (memory_start  != NULL);
        can_init &= (memory_size   >= memory_size_min); 
        can_init &= (capacity      != 0);
        can_init &= (max_load_p100 <= 1.0f);
        can_init &= (max_load_p100 >  0.0f);
        assert(can_init);

        // calculate sizes
        constexpr u32 size_manager       = sizeof(transform_manager);
        constexpr u32 size_table         = sizeof(transform_table);
        const     u32 size_sparse_memory = sparse_index_array::calculate_memory_size(capacity);
        const     u32 max_count          = (u32)((f32)capacity * max_load_p100); 

        // create a stack and allocate memory
        auto mngr_stack     = stack((byte*)memory_start, memory_size);
        auto mngr           = mngr_stack.push_struct<transform_manager>();
        auto sparse_memory  = mngr_stack.push(size_sparse_memory); 
        auto tx             = mngr_stack.push_struct<f32>(max_count);
        auto ty             = mngr_stack.push_struct<f32>(max_count);
        auto tz             = mngr_stack.push_struct<f32>(max_count);
        auto sx             = mngr_stack.push_struct<f32>(max_count);
        auto sy             = mngr_stack.push_struct<f32>(max_count);
        auto sz             = mngr_stack.push_struct<f32>(max_count);
        auto rx             = mngr_stack.push_struct<f32>(max_count);
        auto ry             = mngr_stack.push_struct<f32>(max_count);
        auto rz             = mngr_stack.push_struct<f32>(max_count);
        auto sparse_indices = mngr_stack.push_struct<u32>(max_count);

        // check allocations
        can_init &= mngr_stack.is_valid();
        can_init &= (mngr          != NULL);
        can_init &= (sparse_memory != NULL);
        can_init &= (tx            != NULL);
        can_init &= (ty            != NULL);
        can_init &= (tz            != NULL);
        can_init &= (sx            != NULL);
        can_init &= (sy            != NULL);
        can_init &= (sz            != NULL);
        can_init &= (rx            != NULL);
        can_init &= (ry            != NULL);
        can_init &= (rz            != NULL);
        assert(can_init);

        // initialize the manager
        mngr->sparse_indexes           = sparse_index_array(sparse_memory, size_sparse_memory, capacity, max_load_p100);
        mngr->dense_data.translation.x = tx; 
        mngr->dense_data.translation.y = ty; 
        mngr->dense_data.translation.z = tz; 
        mngr->dense_data.scale.x       = sx; 
        mngr->dense_data.scale.y       = sy; 
        mngr->dense_data.scale.z       = sz; 
        mngr->dense_data.rotation.x    = rx; 
        mngr->dense_data.rotation.y    = ry; 
        mngr->dense_data.rotation.z    = rz; 
        mngr->dense_data.sparse_index  = sparse_indices;
        return(mngr);
    }

    IFB_ENG_INTERNAL u32
    transform_calculate_memory_size(
        const u32 capacity,
        const f32 max_load_p100) {

        const u32 dense_count = (u32)((f32)capacity * max_load_p100);

        const u32 size_mngr        = sizeof(transform_manager);
        const u32 size_sparse_data = sparse_index_array::calculate_memory_size(capacity);
        const u32 size_dense_data  = ((sizeof(transform_table) * 3) + sizeof(u32)) * dense_count;
        
        const u32 size_total = (
            size_mngr        +
            size_sparse_data +
            size_dense_data
        );
        return(size_total);
    }

    IFB_ENG_INTERNAL void
    transform_manager_validate(
        transform_manager* const tm) {

        bool is_valid = (tm != NULL);
        if (is_valid) {
            tm->sparse_indexes.validate();           
            is_valid &= (tm->dense_data.translation.x != NULL); 
            is_valid &= (tm->dense_data.translation.y != NULL); 
            is_valid &= (tm->dense_data.translation.z != NULL); 
            is_valid &= (tm->dense_data.scale.x       != NULL); 
            is_valid &= (tm->dense_data.scale.y       != NULL); 
            is_valid &= (tm->dense_data.scale.z       != NULL); 
            is_valid &= (tm->dense_data.rotation.x    != NULL); 
            is_valid &= (tm->dense_data.rotation.y    != NULL); 
            is_valid &= (tm->dense_data.rotation.z    != NULL); 
            is_valid &= (tm->dense_data.sparse_index  != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    transform_manager_info(
        transform_manager* const tm,
        manager_info&            info) {

        transform_manager_validate(tm);

        constexpr u32 entry_size = (
            ((sizeof(f32) * 3) + sizeof(u32)) * 3
        );
        const u32 dense_data_size = entry_size * tm->sparse_indexes.capacity();

        info.size          = dense_data_size + tm->sparse_indexes.size();
        info.capacity      = tm->sparse_indexes.capacity();
        info.count_current = tm->sparse_indexes.count();
        info.count_max     = tm->sparse_indexes.max_count();
    }
};