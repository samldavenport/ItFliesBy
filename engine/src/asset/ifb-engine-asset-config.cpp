#pragma once

#include "ifb-engine-asset-config.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL asset_config_editor_context_t*
    asset_config_editor_arena_alloc(
        eng_mem_arena_t* arena) {

        auto config       = sld::arena_push_struct<asset_config_editor_context_t>(arena);
        auto path         = sld::arena_push_struct<eng_asset_config_cstr_t>(arena);
        auto list_text    = sld::arena_push_struct<asset_config_list_t>(arena);
        auto list_image   = sld::arena_push_struct<asset_config_list_t>(arena);
        auto list_sound   = sld::arena_push_struct<asset_config_list_t>(arena);
        auto list_font    = sld::arena_push_struct<asset_config_list_t>(arena);
        auto list_deleted = sld::arena_push_struct<asset_config_list_t>(arena);

        const bool can_init = (
            config       != NULL &&
            path         != NULL &&
            list_text    != NULL &&
            list_image   != NULL &&
            list_sound   != NULL &&
            list_font    != NULL &&
            list_deleted != NULL
        );
        assert(can_init);

        config->path              = path; 
        config->node_list.text    = list_text;
        config->node_list.image   = list_image;
        config->node_list.sound   = list_sound;
        config->node_list.font    = list_font;
        config->node_list.deleted = list_deleted;
        return(config);
    }

    IFB_ENG_INTERNAL bool
    asset_config_editor_context_is_valid(
        const asset_config_editor_context_t* editor_context) {

        const bool is_valid = (
            editor_context                    != NULL &&
            editor_context->path              != NULL &&
            editor_context->node_list.text    != NULL &&
            editor_context->node_list.image   != NULL &&
            editor_context->node_list.sound   != NULL &&
            editor_context->node_list.font    != NULL &&            
            editor_context->node_list.deleted != NULL            
        );
        return(is_valid);
    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_assert_valid(
        const asset_config_editor_context_t* editor_context) {

        assert(asset_config_editor_context_is_valid(editor_context));
    }


    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_editor_context_add_text(
        asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        asset_config_editor_context_assert_valid(editor_context);

        asset_config_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );

        asset_config_file_list_add_node(
            editor_context->node_list.text,
            node);
    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_editor_context_add_image(
        asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        asset_config_editor_context_assert_valid(editor_context);

        asset_config_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );

        asset_config_file_list_add_node(
            editor_context->node_list.image,
            node);
    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_editor_context_add_sound(
        asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        assert(editor_context);

        asset_config_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );
        
        asset_config_file_list_add_node(
            editor_context->node_list.sound,
            node);
    }

    IFB_ENG_INTERNAL asset_config_node_t*
    asset_config_editor_context_add_font(
        asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        asset_config_editor_context_assert_valid(editor_context);

        asset_config_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );
        
        asset_config_file_list_add_node(
            editor_context->node_list.font,
            node);
    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_name(
        asset_config_editor_context_t* editor_context,
        asset_config_node_t*           file_node,
        const cchar*                       asset_name) {

        asset_config_list_t* list = file_node != NULL ? (asset_config_list_t*)file_node->list : NULL;

        const bool is_valid = (
            asset_config_editor_context_is_valid(editor_context) &&
            editor_context == list->editor_context
        );
        assert(is_valid);

        asset_config_node_update_name(file_node, asset_name);
    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_path(
        asset_config_editor_context_t* editor_context,
        asset_config_node_t*      file_node,
        const cchar*                       asset_path) {

        asset_config_list_t* list = file_node != NULL ? (asset_config_list_t*)file_node->list : NULL;

        const bool is_valid = (
            asset_config_editor_context_is_valid(editor_context) &&
            editor_context == list->editor_context
        );
        assert(is_valid);

        asset_config_node_update_path(file_node, asset_path);
    }

    IFB_ENG_INTERNAL void
    asset_config_editor_delete_file_node(
        asset_config_editor_context_t* editor_context,
        asset_config_node_t*      file_node) {

        asset_config_list_t* list = file_node != NULL ? (asset_config_list_t*)file_node->list : NULL;

        const bool is_valid = (
            asset_config_editor_context_is_valid(editor_context) &&
            editor_context == list->editor_context
        );
        assert(is_valid);

        asset_config_node_t* prev = (asset_config_node_t*)file_node->prev;
        asset_config_node_t* next = (asset_config_node_t*)file_node->next;
        const bool is_first = (file_node == list->head);
        const bool is_last  = (file_node == list->tail); 

        file_node->prev = NULL;
        file_node->next = NULL;

        if (is_first) list->head = next;
        if (is_last)  list->tail = prev;
        if (next)     next->prev = prev;
        if (prev)     prev->next = next;

        asset_config_file_list_add_node(list, file_node);
    }

};