#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include <sld-sparse-array.hpp>

#include "ifb-engine.hpp"
#include "core-entity.hpp"
#include "core-id.hpp"
#include "core-transform.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using sparse_index_array = sparse_array<u32>;

    struct manager_info;
    struct transform_manager;
    struct quad_manager;
    struct entity_manager;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct manager_info {
        u32 size;
        u32 capacity;
        u32 count_current;
        u32 count_max;
    };

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
    IFB_ENG_INTERNAL void entity_manager_info          (entity_manager* const em, manager_info& info);
    IFB_ENG_INTERNAL bool entity_create                (entity_manager* const em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL void entity_lookup                (entity_manager* const em, entity_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    IFB_ENG_INTERNAL void entity_delete                (entity_manager* const em, const entity_id* id, const u32 count = 1);

    //-------------------------------------------------------------------
    // TRANSFORM MANAGER
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL transform_manager*
    transform_manager_init(
        const void* memory_start,
        const u32   memory_size,
        const u32   capacity,
        const f32   max_load_p100
    );
    IFB_ENG_INTERNAL u32  transform_calculate_memory_size (const u32 capacity, const f32 max_load_p100);
    IFB_ENG_INTERNAL void transform_manager_validate      (transform_manager* const tm);
    IFB_ENG_INTERNAL void transform_manager_info          (transform_manager* const tm, manager_info& info);
    
    IFB_ENG_INTERNAL void transform_create                (transform_manager* const tm, transform_id* out_id, const cchar** in_tag_cstr, const u32 in_count = 1);
    
    IFB_ENG_INTERNAL void transform_lookup_translation    (transform_manager* const tm, translation_table& t_tbl);
    IFB_ENG_INTERNAL void transform_lookup_scale          (transform_manager* const tm, scale_table&       s_tbl);
    IFB_ENG_INTERNAL void transform_lookup_rotation       (transform_manager* const tm, rotation_table&    r_tbl);
    
    IFB_ENG_INTERNAL void transform_update_translation    (transform_manager* const tm, const translation*  translation, const transform_id* id, const u32 in_count = 1);
    IFB_ENG_INTERNAL void transform_update_scale          (transform_manager* const tm, const scale*        scale,       const transform_id* id, const u32 in_count = 1);
    IFB_ENG_INTERNAL void transform_update_rotation       (transform_manager* const tm, const rotation*     rotation,    const transform_id* id, const u32 in_count = 1);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------




};

#endif //MANAGERS_HPP