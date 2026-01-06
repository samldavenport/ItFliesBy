#pragma once

#include "managers.hpp"
#include <sld-sparse-array.hpp>
#include <sld-stack.hpp>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct transform_data {
        f32* x;
        f32* y;
        f32* z;
    };
    struct translation_data : transform_data { };
    struct scale_data       : transform_data { };
    struct roation_data     : transform_data { };

    struct transform_manager {
        sparse_index_array sparse_indexes;
        struct {
            translation_data translation;
            scale_data       scale;
            roation_data     rotation;
            u32*             sparse_index;
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
        constexpr u32 size_table         = sizeof(transform_data);
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
        const u32 size_dense_data  = ((sizeof(transform_data) * 3) + sizeof(u32)) * dense_count;
        
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

    IFB_ENG_INTERNAL void
    transform_create(
        transform_manager* const tm,
        transform_id*            out_id,
        const cchar**            in_tag_cstr,
        const u32                in_count) {

        transform_manager_validate(tm);

        bool is_valid = true;
        is_valid &= (out_id      != NULL);
        is_valid &= (in_tag_cstr != NULL);
        is_valid &= (in_count    != 0);
        assert(is_valid);

        for (
            u32 index = 0;
                index < in_count;
              ++index) {

            const auto tag          = entity_tag(in_tag_cstr[index]);
            const auto id           = tag.to_id();
            const u32  dense_index  = tm->sparse_indexes.count();
            const u32  sparse_index = tm->sparse_indexes.insert(id.val, dense_index);
            
            if (sparse_index == SPARSE_ARRAY_INVALID_INDEX) break;

            tm->dense_data.translation.x [dense_index] = 0.0f;
            tm->dense_data.translation.y [dense_index] = 0.0f;
            tm->dense_data.translation.z [dense_index] = 0.0f;
            tm->dense_data.scale.x       [dense_index] = 1.0f;
            tm->dense_data.scale.y       [dense_index] = 1.0f;
            tm->dense_data.scale.z       [dense_index] = 1.0f;
            tm->dense_data.rotation.x    [dense_index] = 0.0f;
            tm->dense_data.rotation.y    [dense_index] = 0.0f;
            tm->dense_data.rotation.z    [dense_index] = 0.0f;
            tm->dense_data.sparse_index  [dense_index] = sparse_index;
        }
    }

    IFB_ENG_INTERNAL void
    transform_lookup_translation(
        transform_manager* const tm,
        translation_table&       t_tbl) {

        transform_manager_validate(tm);
        t_tbl.validate();
    
        for_count_u32(row, t_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = t_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // get the dense data
            t_tbl.data.x [row] = tm->dense_data.translation.x [dense_index];
            t_tbl.data.y [row] = tm->dense_data.translation.y [dense_index];
            t_tbl.data.z [row] = tm->dense_data.translation.z [dense_index];
        }
    }

    IFB_ENG_INTERNAL void
    transform_lookup_scale(
        transform_manager* const tm,
        scale_table&             s_tbl) {

        transform_manager_validate(tm);
        s_tbl.validate();
        
        for_count_u32(row, s_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = s_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // get the dense data
            s_tbl.data.x[row] = tm->dense_data.scale.x [dense_index];
            s_tbl.data.y[row] = tm->dense_data.scale.y [dense_index];
            s_tbl.data.z[row] = tm->dense_data.scale.z [dense_index];
        }
    }

    IFB_ENG_INTERNAL void
    transform_lookup_rotation(
        transform_manager* const tm,
        rotation_table&          r_tbl) {

        transform_manager_validate(tm);
        r_tbl.validate();
        
        for_count_u32(row, r_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = r_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // get the dense data
            r_tbl.data.x[row] = tm->dense_data.rotation.x [dense_index];
            r_tbl.data.y[row] = tm->dense_data.rotation.y [dense_index];
            r_tbl.data.z[row] = tm->dense_data.rotation.z [dense_index];
        }
    }

    IFB_ENG_INTERNAL void
    transform_update_translation(
        transform_manager* const tm,
        translation_table&       t_tbl) {

        transform_manager_validate(tm);
        t_tbl.validate();

        for_count_u32(row, t_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = t_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // update the dense data
            tm->dense_data.rotation.x [dense_index] = t_tbl.data.x[row];
            tm->dense_data.rotation.y [dense_index] = t_tbl.data.y[row];
            tm->dense_data.rotation.z [dense_index] = t_tbl.data.z[row];
        }
    }

    IFB_ENG_INTERNAL void
    transform_update_scale(
        transform_manager* const tm,
        scale_table&             s_tbl) {

        transform_manager_validate(tm);
        s_tbl.validate();

        for_count_u32(row, s_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = s_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // update the dense data
            tm->dense_data.scale.x [dense_index] = s_tbl.data.x[row];
            tm->dense_data.scale.y [dense_index] = s_tbl.data.y[row];
            tm->dense_data.scale.z [dense_index] = s_tbl.data.z[row];
        }
    }

    IFB_ENG_INTERNAL void
    transform_update_rotation(
        transform_manager* const tm,
        rotation_table&          r_tbl) {

        transform_manager_validate(tm);
        r_tbl.validate();

        for_count_u32(row, r_tbl.count) {

            // look up the sparse index for the transform
            const transform_id id           = r_tbl.data.id[row];
            const u32          sparse_index = tm->sparse_indexes.lookup_sparse_index(id.val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);

            // get the dense index
            // it should always be less than the current count
            const u32 dense_index = tm->sparse_indexes[sparse_index];
            assert(dense_index < tm->sparse_indexes.count());

            // update the dense data
            tm->dense_data.rotation.x [dense_index] = r_tbl.data.x[row];
            tm->dense_data.rotation.y [dense_index] = r_tbl.data.y[row];
            tm->dense_data.rotation.z [dense_index] = r_tbl.data.z[row];
        }
    }
};