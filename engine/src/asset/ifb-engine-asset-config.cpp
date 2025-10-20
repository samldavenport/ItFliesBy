#pragma once

#include "ifb-engine-asset-config.hpp"

namespace ifb {

    IFB_ENG_INTERNAL eng_asset_config_editor_context_t*
    asset_config_editor_context_init(
        eng_mem_arena_t* arena) {

        assert(arena);

        auto config = sld::arena_push_struct<eng_asset_config_editor_context_t>(arena);
        assert(config);

        return(config);
    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_text(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        assert(editor_context);

        eng_asset_config_file_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );

        asset_config_file_list_add_node(
            &editor_context->file_list.text,
            text_node);
    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_image(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        assert(editor_context);

        eng_asset_config_file_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );

        asset_config_file_list_add_node(
            &editor_context->file_list.image,
            text_node);
    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_sound(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        assert(editor_context);

        eng_asset_config_file_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );
        
        asset_config_file_list_add_node(&editor_context->file_list.sound, text_node);
    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_font(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        assert(editor_context);

        eng_asset_config_file_node_t* node = asset_config_arena_alloc_and_init_file_node(
            arena,
            asset_name,
            asset_path
        );
        
        asset_config_file_list_add_node(&editor_context->file_list.font, text_node);
    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_name(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  asset_name) {

    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_path(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  asset_path) {

    }

    IFB_ENG_INTERNAL void
    asset_config_editor_delete_file_node(
        eng_asset_config_file_node_t* file_node) {

    }

};