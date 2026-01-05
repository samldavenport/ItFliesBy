#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include "ifb-engine.hpp"
#include "core-entity.hpp"
namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct transform_manager;
    struct quad_manager;
    struct entity_manager;

    //-------------------------------------------------------------------
    // ENTITY MANAGER
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL entity_manager*
    entity_manager_init(
        const void* memory_start,
        const u32   memory_size, 
        const u32   capacity,
        const f32   max_load_p100
    );
    IFB_ENG_INTERNAL u32  entity_calculate_memory_size (const u32 capacity, const f32 max_load_p100);
    IFB_ENG_INTERNAL void entity_manager_validate      (entity_manager* const em);
    IFB_ENG_INTERNAL u32  entity_capacity              (entity_manager* const em);
    IFB_ENG_INTERNAL u32  entity_count                 (entity_manager* const em);
    IFB_ENG_INTERNAL u32  entity_max_count             (entity_manager* const em);
    IFB_ENG_INTERNAL bool entity_create                (entity_manager* const em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL void entity_lookup                (entity_manager* const em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL void entity_delete                (entity_manager* const em, const entity_id* id, const u32 count = 1);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------




};

#endif //MANAGERS_HPP