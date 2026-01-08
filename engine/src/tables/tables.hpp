#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <sld-sparse-array.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-entity.hpp"
#include "ifb-engine-components.hpp"
#include "math.hpp"
#include "memory.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using entity_index_array = sparse_array<entity_id>;
    using entity_index_cache = array_list<u32>;

    // base
    struct tables;
    struct table_base;
    struct table_page;

    // entities
    struct entity_table;

    // transforms
    struct transform_table;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    static void table_base_validate    (table_base* const table);

    static void entity_table_validate  (entity_table* const in_table);
    static void entity_table_insert    (entity_table* const in_table, const u32 in_count, const cchar**     in_tag_cstr, entity_id* out_id);
    static void entity_table_lookup    (entity_table* const in_table, const u32 in_count, const entity_id*  in_id,       entity*    out_entity);
    static void entity_table_delete    (entity_table* const in_table, const u32 in_count, const entity_id*  in_id);

    static void transform_table_insert (transform_table* const in_table, const u32 in_count, const entity_id* in_id, transform* in_transform);
    static void transform_table_lookup (transform_table* const in_table, const u32 in_count, const entity_id* in_id, transform* out_transform);
    static void transform_table_update (transform_table* const in_table, const u32 in_count, const entity_id* in_id, transform* in_transform);
    static void transform_table_delete (transform_table* const in_table, const u32 in_count, const entity_ud* in_id);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct tables {
        entity_table*    entity;
        transform_table* transform;
    };

    struct table_page_base {
        table_page* next;
        table_page* prev;
    };

    struct table_base {
        entity_index_array index_array;
        entity_index_cache index_cache;
        u32                count_total;
        u32                count_per_page;
        table_page*        page_list;
    };

    struct entity_table : table_base {
        struct page : table_page_base {
            entity_id*  id;
            entity_tag* tag;
        } pages;
    };

    struct transform_table : table_base {
        struct page : table_page_base {
            translation* translation;
            scale*       scale;
            rotation*    rotation;
        } pages;
    };

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    static tables _tables;
};

#endif //CORE_TRANSFORM_HPP
