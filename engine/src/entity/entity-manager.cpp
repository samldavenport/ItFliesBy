#pragma once

#include "entity.hpp"
#include <sld-stack.hpp>

namespace ifb::eng {

    using sparse_index_array = sparse_array<u32>; 

    struct entity_manager {
        sparse_index_array index_array;
        struct {
            entity_id*  id;
            entity_tag* tag;
            u32*        sparse_index;
        } data;
    };

    IFB_ENG_INTERNAL entity_manager*
    entity_manager_init(
        const void* memory_start,
        const u32   memory_size, 
        const u32   capacity,
        const f32   max_load_p100) {

        const u32 min_memory_size = entity_calculate_memory_size(
            capacity,
            max_load_p100);

        bool can_init = true;
        can_init &= (memory_start  != NULL);
        can_init &= (memory_size   >= min_memory_size); 
        can_init &= (capacity      != 0);
        can_init &= (max_load_p100 <= 1.0f);
        can_init &= (max_load_p100 >  0.0f);
        assert(can_init);

        // create stack
        stack mngr_stack((byte*)memory_start, memory_size);
        
        // allocate manager
        auto mngr = mngr_stack.push_struct<entity_manager>();
        assert(mngr);

        // allocate sparse memory
        const u32 sparse_memory_size  = mngr->index_array.calculate_memory_size(capacity);
        void*     sparse_memory_start = (void*)mngr_stack.push(sparse_memory_size); 

        // initialize sparse array
        mngr->index_array = sparse_index_array(
            sparse_memory_start,
            sparse_memory_size,
            capacity,
            max_load_p100
        );
        mngr->index_array.validate();

        // allocate data arrays  
        const u32 max_count = mngr->index_array.max_count();
        mngr->data.id           = mngr_stack.push_struct<entity_id>  (max_count);
        mngr->data.tag          = mngr_stack.push_struct<entity_tag> (max_count); 
        mngr->data.sparse_index = mngr_stack.push_struct<u32>        (max_count);
        assert(
            mngr->data.id                 != NULL &&
            mngr->data.tag                != NULL &&
            mngr->data.sparse_index != NULL
        );

        return(mngr);
    }

    IFB_ENG_INTERNAL u32
    entity_calculate_memory_size(
        const u32 capacity,
        const f32 max_load_p100) {

        const u32 dense_count = (u32)((f32)capacity * max_load_p100);

        const u32 size_mngr        = sizeof(entity_manager);
        const u32 size_sparse_data = sparse_index_array::calculate_memory_size(capacity);
        const u32 size_dense_data  = (sizeof(entity_id) + sizeof(entity_tag) + sizeof(u32)) * dense_count;
        
        const u32 size_total = (
            size_mngr        +
            size_sparse_data +
            size_dense_data
        );
        return(size_total);
    }

    IFB_ENG_INTERNAL void
    entity_manager_validate(
        const entity_manager* em) {

        bool is_valid = (em != NULL);
        if (is_valid) {

            em->index_array.validate();

            is_valid &= (em->data.id           != NULL);
            is_valid &= (em->data.tag          != NULL);
            is_valid &= (em->data.sparse_index != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL u32
    entity_capacity(
        const entity_manager* em) {

        entity_manager_validate(em);
        return(em->index_array.capacity());
    }

    IFB_ENG_INTERNAL u32
    entity_count(
        const entity_manager* em) {

        entity_manager_validate(em);
        return(em->index_array.count());
    }

    IFB_ENG_INTERNAL u32 
    entity_max_count(
        const entity_manager* em) {

        entity_manager_validate(em);
        return(em->index_array.max_count());
    }

    IFB_ENG_INTERNAL bool
    entity_create(
        const entity_manager* em,
        entity_id*            out_id,
        const cchar**         in_tag_cstr,
        const u32             in_count) {

        entity_manager_validate(em);
        assert(
            out_id      != NULL &&
            in_tag_cstr != NULL &&
            in_count    != 0
        );

        for (
            u32 entity = 0;
                entity < in_count;
              ++entity) {

            const entity_tag tag(in_tag_cstr[entity]);
            const entity_id  id = tag.to_id();

        }

    }

    IFB_ENG_INTERNAL bool entity_lookup                (const entity_manager* em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count);
    IFB_ENG_INTERNAL bool entity_delete                (const entity_manager* em, const entity_id* id, const u32 count);


};