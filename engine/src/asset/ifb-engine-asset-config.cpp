#pragma once

#include "ifb-engine-asset-config.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONTEXT
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL bool
    asset_config_context_is_valid(
        asset_config_context_t& context) {

        bool is_valid = (
            context.working_directory != NULL &&
            context.name              != NULL &&
            context.path              != NULL &&
            context.node_list.text    != NULL &&
            context.node_list.image   != NULL &&
            context.node_list.sound   != NULL &&
            context.node_list.font    != NULL &&
            context.node_list.deleted != NULL &&
            context.active_arena      != NULL
        );
        return(is_valid);
    }


    IFB_ENG_INTERNAL void
    asset_config_context_create(
        asset_config_context_t& context) {

        constexpr u64 alctr_size_total = sld::size_gigabytes(1);
        constexpr u64 alctr_size_arena = sld::size_megabytes(1);

        arena_allocator_t arena_alctr;
        sld::arena_allocator_reserve_os_memory(
            &arena_alctr,
            alctr_size_total,
            alctr_size_arena);

        arena_t* arena = sld::arena_allocator_commit(&arena_alctr);
        assert(arena);

        auto strings = string_c32_arena_alloc        (arena, 2); 
        auto lists   = asset_config_list_arena_alloc (arena, 5); 
        auto alctr   = sld::arena_push_struct<arena_allocator_t>(arena); 

        assert(
            strings != NULL &&
            lists   != NULL &&            
            alctr   != NULL
        );

        *alctr = arena_alctr;

        context.working_directory = eng_file_mngr_get_working_directory(); 
        context.name              = &strings[0];
        context.path              = &strings[1];
        context.node_list.text    = &lists[0];
        context.node_list.image   = &lists[1];
        context.node_list.sound   = &lists[2];
        context.node_list.font    = &lists[3];
        context.node_list.deleted = &lists[4];
        context.arena_allocator   = alctr;
        context.active_arena      = arena;
    }

    IFB_ENG_INTERNAL void
    asset_config_context_destroy(
        asset_config_context_t& context) {

        sld::arena_allocator_release_os_memory(context.arena_allocator);

        context.working_directory = NULL;    
        context.name              = NULL;
        context.path              = NULL;
        context.node_list.text    = NULL;
        context.node_list.image   = NULL;
        context.node_list.sound   = NULL;
        context.node_list.font    = NULL;
        context.node_list.deleted = NULL;
        context.active_arena      = NULL;
    }
    
    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_context_add_text_node (
        asset_config_context_t& context,
        const cchar*            name,
        const cchar*            path) {

        asset_config_node_t* node = asset_config_list_add_new_node(
            context.node_list.text,
            context.active_arena,
            name,
            path
        );

        return(node);
    } 

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_context_add_image_node(
        asset_config_context_t& context,
        const cchar* name,
        const cchar* path) {

    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_context_add_sound_node(
        asset_config_context_t& context,
        const cchar* name,
        const cchar* path) {

    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_context_add_font_node (
        asset_config_context_t& context,
        const cchar* name,
        const cchar* path) {

    }

    //-------------------------------------------------------------------
    // CONFIG_NODES
    //-------------------------------------------------------------------
    
    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_node_arena_alloc(
        eng_mem_arena_t* arena) {

        auto node = sld::arena_push_struct<asset_config_node_t>(arena);
        auto cstr = string_c32_arena_alloc(arena); 

        assert(node != NULL && cstr != NULL);

        node->data.name = &cstr[0];
        node->data.path = &cstr[1];
        node->list      = NULL;
        node->next      = NULL;
        node->prev      = NULL;
        return(node);
    }

    IFB_ENG_INTERNAL void
    asset_config_node_init(
        asset_config_node_t* node,
        const cchar*         name,
        const cchar*         path) {

        assert(
            node            != NULL &&
            node->data.name != NULL &&
            node->data.path != NULL &&
            name            != NULL &&
            path            != NULL &&
            name[0]         != 0    &&
            path[0]         != 0
        );

        const u32 bytes_copied_name = string_c32_copy_from(node->data.name, name);
        const u32 bytes_copied_path = string_c32_copy_from(node->data.path, path);
        assert(bytes_copied_name != 0 && bytes_copied_path != 0);
    
        string_c32_sanitize(node->data.name);
    }

    IFB_ENG_INTERNAL void
    asset_config_node_update_name(
        asset_config_node_t* node,
        const cchar*         name) {

        assert(
            node            != NULL &&
            node->data.name != NULL &&
            name            != NULL &&
            name[0]         != 0
        );

        const u32 bytes_copied_name = string_c32_copy_from(node->data.name, name);
        assert(bytes_copied_name != 0);        

        // sanitize the name
        string_c32_sanitize(node->data.name);


    }

    IFB_ENG_INTERNAL void
    asset_config_node_update_path(
        asset_config_node_t* node,
        const cchar*         path) {

        assert(
            node            != NULL &&
            node->data.path != NULL &&
            path            != NULL &&
            path[0]         != 0
        );

        const u32 bytes_copied_path = string_c32_copy_from(node->data.path, path);
        assert(bytes_copied_path != 0);
    }

    //-------------------------------------------------------------------
    // CONFIG LIST
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL asset_config_list_t*
    asset_config_list_arena_alloc(
        eng_mem_arena_t* arena, const u32 count) {

        auto list = (asset_config_list_t*)sld::dl_list_arena_alloc<asset_config_node_t*>(arena, count);
        assert(list);
        return(list);
    }

    IFB_ENG_INTERNAL void
    asset_config_list_remove_node(
        asset_config_list_t* file_list,
        asset_config_node_t* file_node) {

        assert(file_list != NULL && file_node != NULL);
        sld::dl_list_remove(file_list, file_node);
    }

    IFB_ENG_INTERNAL void
    asset_config_list_add_existing_node(
        asset_config_list_t* list,
        asset_config_node_t* node) {

        const bool did_insert = sld::dl_list_insert_at_tail(list, node);
        assert(did_insert);
    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_list_add_new_node(
        asset_config_list_t* list,
        arena_t*             arena,
        const cchar*         name,
        const cchar*         path) {

        assert(
            list  != NULL &&
            arena != NULL &&
            name  != NULL &&
            path  != NULL
        );

        asset_config_node_t* node =  asset_config_node_arena_alloc(arena);
        asset_config_node_init              (node, name, path);
        asset_config_list_add_existing_node (list, node);

        return(node);
    }
};