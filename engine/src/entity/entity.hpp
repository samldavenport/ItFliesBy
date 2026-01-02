#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ifb-engine.hpp"
#include "core.hpp"
#include "entity-id.hpp"
#include "entity-tag.hpp"
#include "entity-sparse-array.hpp"
#include <sld-sparse-set.hpp>
#include <sld-array-list.hpp>
namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct entity;
    struct entity_id;
    struct entity_index;
    struct entity_tag;
    struct entity_manager;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    entity_manager*
    entity_manager_init(
        const void* memory_start,
        const u32   memory_size, 
        const u32   capacity,
        const f32   max_load_p100
    );

    u32  entity_calculate_memory_size (const u32 capacity, const f32 max_load_p100);
    u32  entity_capacity              (entity_manager* em const);
    u32  entity_count                 (entity_manager* em const);
    u32  entity_max_count             (entity_manager* em const);
    bool entity_create                (entity_manager* em const, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    bool entity_lookup                (entity_manager* em const, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    bool entity_delete                (entity_manager* em const, const entity_id* id, const u32 count = 1);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_index {
        u32 sparse;
        u32 dense;
    };

    struct entity {
        entity_tag*  tag;
        entity_index index;
        entity_id    id;
    };
        
    class entity_manager {
    
    private:

        sparse_array<u32> _sparse_data_index_array;
        struct {
            entity_id*  id;
            entity_tag* tag;
            u32*        sparse_array_index;
        } _data;

    public:

        void init(
            const void* memory_start,
            const u32   memory_size, 
            const u32   capacity,
            const f32   max_load_p100
        );
        
        u32  calculate_memory_size (const u32 capacity, const f32 max_load_p100) const;
        u32  capacity              (void) const;
        u32  count                 (void) const;
        u32  max_count             (void) const;

        bool create_entities (entity_id* out_id, const cchar** in_tag_cstr, const u32 count = 1);
        bool lookup_entities (entity_id* out_id, const cchar** in_tag_cstr, const u32 count = 1);
        bool delete_entities (const entity_id* id, const u32 count = 1);
    };

    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        

        return(true);
    }
};

#endif //ENTITY_HPP