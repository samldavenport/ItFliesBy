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

    IFB_ENG_INTERNAL entity_manager*
    entity_manager_init(
        const void* memory_start,
        const u32   memory_size, 
        const u32   capacity,
        const f32   max_load_p100
    );

    IFB_ENG_INTERNAL u32  entity_calculate_memory_size (const u32 capacity, const f32 max_load_p100);
    IFB_ENG_INTERNAL void entity_manager_validate      (const entity_manager* em);
    IFB_ENG_INTERNAL u32  entity_capacity              (const entity_manager* em);
    IFB_ENG_INTERNAL u32  entity_count                 (const entity_manager* em);
    IFB_ENG_INTERNAL u32  entity_max_count             (const entity_manager* em);
    IFB_ENG_INTERNAL bool entity_create                (const entity_manager* em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL bool entity_lookup                (const entity_manager* em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL bool entity_delete                (const entity_manager* em, const entity_id* id, const u32 count = 1);

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
        


    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        

        return(true);
    }
};

#endif //ENTITY_HPP