#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ifb-engine.hpp"
#include "core.hpp"
#include "entity-id.hpp"
#include "entity-tag.hpp"
#include "entity-sparse-array.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct entity;
    struct entity_id;
    struct entity_index;
    struct entity_tag;
    struct entity_manager;
    struct entity_sparse_array;
    struct entity_sparse_entry;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL u32       entity_memory_size            (const u32 entity_count, const f32 max_load = 0.7);
    IFB_ENG_INTERNAL void      entity_manager_init           (entity_manager* em, const void* memory, const u32 size, const f32 max_load = 0.7);
    IFB_ENG_INTERNAL entity_id entity_create                 (entity_manager* em, const cchar* tag_cstr);
    IFB_ENG_INTERNAL void      entity_delete                 (entity_manager* em, const entity_id id);
    IFB_ENG_INTERNAL bool      entity_lookup_by_id           (entity_manager* em, entity& entity);
    IFB_ENG_INTERNAL bool      entity_lookup_by_sparse_index (entity_manager* em, entity& entity);
    IFB_ENG_INTERNAL bool      entity_lookup_by_dense_index  (entity_manager* em, entity& entity);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_index {
        u32 sparse;
        u32 dense;
    };

    struct entity {
        entity_tag*  tag;
        entity_id    id;
        entity_index index;
    };

    struct entity_manager {
        entity_sparse_array sparse_array;
        struct {
            entity_tag* tag;
        } dense_array;
    };

    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        entity_tag tag;
        tag.init("TEST TAG");
        entity_id  id = tag.to_id();

        entity_sparse_array sparse_array;
        sparse_array.init(entity_memory, ENTITY_MEMORY_SIZE);

        
        bool result = false;

        u32 index = 0;
        result = sparse_array.lookup(id, index); 
        assert(!result);

        result = sparse_array.insert(id, 5);
        assert(result);

        result = sparse_array.lookup(id, index);
        assert(result);

        entity_sparse_entry entry = sparse_array[index];
        assert(
            entry.id.val == id.val &&
            entry.val    == 5 
        );

        return(true);
    }
};

#endif //ENTITY_HPP