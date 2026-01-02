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

    IFB_ENG_INTERNAL u32                 entity_memory_size  (const u32 entity_count, const f32 max_load = 0.7);
    IFB_ENG_INTERNAL entity_manager*     entity_manager_init (const void* memory, const u32 size, const f32 max_load = 0.7);
    IFB_ENG_INTERNAL bool                entity_create       (entity_manager* em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL bool                entity_delete       (entity_manager* em, const entity_id* id, const u32 count = 1);
    IFB_ENG_INTERNAL const entity_table& entity_get_table    (entity_manager* em);

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

    struct entity_table {
        u32         capacity;
        u32         count;
        struct {
            entity_id*  id;
            entity_tag* tag;
            u32*        sparse_index;
        } data;
    };

    class entity_manager {

    private:

        entity_sparse_array _sparse_array;
        entity_dense_array  _dense_array;
    
    public:

        // static 
        static u32 calculate_memory_requirement (const u32 entity_count, const f32 max_load);

        // constructor        
        explicit   entity_manager (const void* memory_ptr, const u32 memory_size, const f32 max_load);

        // methods
        bool              create_entities  (entity_id* out_id,   const cchar** in_tag_cstr, const u32 count = 1);
        bool              lookup_entities  (entity_id* out_id,   const cchar** in_tag_cstr, const u32 count = 1);
        void              delete_entities  (const entity_id* id, const u32 count = 1);
        const u32         get_entity_count (void);
        const entity_tag* get_tag_array    (void);
        const entity_id*  get_id_array     (void);
    };

    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        entity_tag tag;
        tag.init("TEST TAG");
        entity_id  id = tag.to_id();

        entity_sparse_array sparse_array(entity_memory, ENTITY_MEMORY_SIZE);

        
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