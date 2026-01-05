#pragma once

#include "managers.hpp"
#include "core-entity.hpp"
#include <sld-stack.hpp>
#include <sld-sparse-array.hpp>

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
        entity_manager* const em) {

        bool is_valid = (em != NULL);
        if (is_valid) {

            em->index_array.validate();

            is_valid &= (em->data.id           != NULL);
            is_valid &= (em->data.tag          != NULL);
            is_valid &= (em->data.sparse_index != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_INTERNAL void
    entity_manager_info(
        entity_manager* const em,
        manager_info&         info) {

        entity_manager_validate(em);

        constexpr u32 entry_size = (
            sizeof(entity_id)  +
            sizeof(entity_tag) +
            sizeof(u32)
        );

        info.size          = (entry_size * em->index_array.capacity()) + em->index_array.size();
        info.capacity      = em->index_array.capacity();
        info.count_current = em->index_array.count();
        info.count_max     = em->index_array.max_count();
    }

    IFB_ENG_INTERNAL bool
    entity_create(
        entity_manager* const em,
        entity_id*            out_id,
        const cchar**         in_tag_cstr,
        const u32             in_count) {

        entity_manager_validate(em);
        assert(
            out_id      != NULL &&
            in_tag_cstr != NULL &&
            in_count    != 0
        );

        bool did_create = true;

        for (
            u32 entity = 0;
                entity < in_count;
              ++entity) {

            // get the data
            const u32    dense_index = em->index_array.count();
            entity_tag&  tag         = em->data.tag [dense_index];
            const cchar* tag_cstr    = in_tag_cstr  [entity];
            entity_id&   id          = out_id       [entity];

            // create the tag and id
            tag = entity_tag(tag_cstr);
            id  = tag.to_id();

            // add the id and dense index to the sparse array
            const u32 sparse_index = em->index_array.insert(
                id.val,     // key
                dense_index // value
            );

            // if we didn't add the id, we're done
            if (sparse_index == SPARSE_ARRAY_INVALID_INDEX) {
                did_create = false;
                id         = ENTITY_ID_INVALID;
                break;
            }

            // update the dense arrays
            em->data.id           [dense_index] = id;
            em->data.tag          [dense_index] = tag;
            em->data.sparse_index [dense_index] = sparse_index;
        }

        return(did_create);
    }

    IFB_ENG_INTERNAL void
    entity_lookup(
        entity_manager* const em,
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

            entity_id&   id       = out_id      [entity];
            const cchar* tag_cstr = in_tag_cstr [entity];

            const entity_tag tag(tag_cstr);
            const entity_id  tmp_id = tag.to_id();

            const u32 sparse_index = em->index_array.lookup_sparse_index(tmp_id.val);

            id.val = (sparse_index != SPARSE_ARRAY_INVALID_INDEX)
                ? em->index_array[sparse_index]
                : ENTITY_ID_INVALID;
        }

    }

    IFB_ENG_INTERNAL void
    entity_delete(
        entity_manager* const em,
        const entity_id*      id,
        const u32             count) {

        entity_manager_validate(em);
        assert(
            id    != NULL &&
            count != 0    &&
            count <= em->index_array.count()
        );

        for (
            u32 delete_index = 0;
                delete_index < count;
              ++delete_index) {

            // get the info for the last element
            const u32         last_index_dense  = em->index_array.count() - 1;
            const u32         last_index_sparse = em->data.sparse_index [last_index_dense]; 
            const entity_id   last_entity_id    = em->data.id           [last_index_dense];
            const entity_tag& last_tag          = em->data.tag          [last_index_dense];

            // lookup the sparse index of the entity to delete
            // it should always exist
            const u32 sparse_index = em->index_array.lookup_sparse_index(id[delete_index].val);
            assert(sparse_index != SPARSE_ARRAY_INVALID_INDEX);            

            // get the dense index info
            const u32 dense_index     = em->index_array[sparse_index]; 
            const u32 dense_to_sparse = em->data.sparse_index[delete_index]; 

            // we can safely remove the sparse data
            em->index_array.remove(sparse_index);

            // if the delete element is the last one, nothing else to do
            if (last_index_dense == dense_index) continue;

            // copy dense data
            em->data.id           [dense_index] = last_entity_id;
            em->data.tag          [dense_index] = last_tag;
            em->data.sparse_index [dense_index] = last_index_sparse;

            // copy sparse data
            em->index_array[last_index_sparse] = dense_index;
        }
    }
};