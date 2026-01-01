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
    struct entity_tag;
    struct entity_manager;
    struct entity_sparse_array;
    struct entity_sparse_entry;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    entity_manager* entity_manager_init (const void* memory, const u32 size);
    entity_id       entity_create       (entity_manager* em, const cchar* tag_cstr);
    bool            entity_delete       (entity_manager* em, const entity_id id);
    entity          entity_lookup       (entity_manager* em, const entity_id id);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity {
        entity_id   id;
        entity_tag* tag;
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