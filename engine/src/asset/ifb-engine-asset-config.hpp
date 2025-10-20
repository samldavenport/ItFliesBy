#ifndef IFB_ENGINE_ASSET_CONFIG_HPP
#define IFB_ENGINE_ASSET_CONFIG_HPP

#include <sld-arena.hpp>
#include <sld-double-linked-list.hpp>
#include "ifb-engine.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"

using namespace ifb;
namespace ifb::eng {

    constexpr u32   ASSET_CONFIG_CSTR_LENGTH        = 32;
    constexpr cchar ASSET_CONFIG_NODE_NAME_TEXT  [] = "text";
    constexpr cchar ASSET_CONFIG_NODE_NAME_IMAGE [] = "image";
    constexpr cchar ASSET_CONFIG_NODE_NAME_SOUND [] = "sound";
    constexpr cchar ASSET_CONFIG_NODE_NAME_FONT  [] = "font";
    constexpr cchar ASSET_CONFIG_DEFAULT_CONFIG  [] = 
        "<ifb-assets>"
            "<text path=\"../assets/text\"></text>"
            "<image path=\"../assets/image\"></image>"
            "<sound path=\"../assets/sound\"></sound>"
            "<font path=\"../assets/font\"></font>"
        "</ifb-assets>";

    struct asset_config_cstr_t;
    struct asset_config_list_t;
    struct asset_config_node_t;
    struct asset_config_node_data_t;
    struct asset_config_editor_context_t;

    IFB_ENG_INTERNAL asset_config_cstr_t*           asset_config_cstr_arena_alloc                     (eng_mem_arena_t* arena);
    IFB_ENG_INTERNAL void                           asset_config_cstr_update                          (asset_config_cstr_t* config_cstr, const cchar* value);

    IFB_ENG_INTERNAL asset_config_node_t*           asset_config_node_arena_alloc                     (eng_mem_arena_t* arena);
    IFB_ENG_INTERNAL void                           asset_config_node_init                            (asset_config_node_t* node, const cchar* name, const cchar* path);
    IFB_ENG_INTERNAL void                           asset_config_node_update_name                     (asset_config_node_t* node, const cchar* name);
    IFB_ENG_INTERNAL void                           asset_config_node_update_path                     (asset_config_node_t* node, const cchar* path);

    IFB_ENG_INTERNAL asset_config_list_t*           asset_config_list_arena_alloc                     (eng_mem_arena_t*);
    IFB_ENG_INTERNAL void                           asset_config_list_add_node                        (asset_config_list_t* file_list, asset_config_node_t* file_node);
    IFB_ENG_INTERNAL void                           asset_config_list_remove_node                     (asset_config_list_t* file_list, asset_config_node_t* file_node);

    IFB_ENG_INTERNAL asset_config_editor_context_t* asset_config_editor_context_arena_alloc           (eng_mem_arena_t* arena);
    IFB_ENG_INTERNAL bool                           asset_config_editor_context_is_valid              (const asset_config_editor_context_t* editor_context);
    IFB_ENG_INTERNAL void                           asset_config_editor_context_assert_valid          (const asset_config_editor_context_t* editor_context);
    IFB_ENG_INTERNAL asset_config_node_t*           asset_config_editor_context_add_text              (asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL asset_config_node_t*           asset_config_editor_context_add_image             (asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL asset_config_node_t*           asset_config_editor_context_add_sound             (asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL asset_config_node_t*           asset_config_editor_context_add_font              (asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL void                           asset_config_editor_context_update_file_node_name (asset_config_editor_context_t* editor_context, asset_config_node_t* file_node, const cchar* asset_name);
    IFB_ENG_INTERNAL void                           asset_config_editor_context_update_file_node_path (asset_config_editor_context_t* editor_context, asset_config_node_t* file_node, const cchar* asset_path);
    IFB_ENG_INTERNAL void                           asset_config_editor_delete_file_node              (asset_config_editor_context_t* editor_context, asset_config_node_t* file_node);

    struct asset_config_cstr_t {
        cchar chars[]
    };

    struct asset_config_node_data_t {
        eng_asset_cstr_t* name;
        eng_asset_cstr_t* path;
    };  

    struct asset_config_node_t : sld::dl_node_t<asset_config_node_data_t> { }; 
    struct asset_config_list_t : sld::dl_list_t<asset_config_node_data_t> {
        asset_config_editor_context_t* editor_context;
    };

    struct asset_config_editor_context_t {
        eng_asset_config_cstr_t* path;
        struct {
            asset_config_list_t* text;
            asset_config_list_t* image;
            asset_config_list_t* sound;
            asset_config_list_t* font;
            asset_config_list_t* deleted;
        } node_list;
    };

    IFB_ENG_INTERNAL_INLINE asset_config_node_t* 
    asset_config_arena_alloc_file_node(eng_mem_arena_t* arena) {

        auto node         = sld::arena_push_struct<asset_config_node_t> (arena); 
        auto string_array = sld::arena_push_struct<eng_asset_cstr_t>    (arena, 2);
        
        assert(node != NULL && string_array != NULL);

        node->data.name = &string_array[0];
        node->data.path = &string_array[1];
        return(node);
    };

    IFB_ENG_INTERNAL_INLINE asset_config_node_t*
    asset_config_arena_alloc_and_init_file_node(
        eng_mem_arena_t* arena,
        const cchar*     asset_name,
        const cchar*     asset_path) {

        const bool can_init = (
            arena      != NULL &&
            asset_name != NULL &&
            asset_path != NULL
        );

        assert(can_init);

        asset_config_node_t* node = asset_config_arena_alloc_file_node(arena);
        asset_config_node_update_name (node, asset_name);
        asset_config_node_update_path (node, asset_path);
        return(node);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_node_update_name(
        asset_config_node_t* node,
        const cchar*         name_src_cchar) {

        assert(
            node           != NULL &&
            node->data.name     != NULL &&
            name_src_cchar != NULL
        );

        eng_asset_cstr_t* name = node->data.name;
        cstr_t    dst          = { name->chars, IFB_ENG_ASSET_CSTR_SIZE};
        const u32 bytes_copied = sld::cstr_copy_from(&dst, name_src_cchar, IFB_ENG_ASSET_CSTR_SIZE);

        assert(
            bytes_copied >  0 &&
            bytes_copied <= IFB_ENG_ASSET_CSTR_SIZE
        );

        eng_asset_name_sanitize(1, node->data.name);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_file_list_add_node(
        asset_config_list_t* file_list,
        asset_config_node_t* file_node) {

        assert(file_list != NULL && file_node != NULL);

        const bool did_insert = sld::dl_list_insert_at_tail(file_list, file_node);
        assert(did_insert);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_file_list_remove_node(
        asset_config_list_t* file_list,
        asset_config_node_t* file_node) {
        
        
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_node_update_path(
        asset_config_node_t* file_node,
        const cchar*         path_src_cchar) {

        assert(
            file_node            != NULL &&
            file_node->data.path != NULL &&
            path_src_cchar       != NULL
        );

        eng_asset_cstr_t* path = file_node->data.path;
        cstr_t    dst          = { path->chars, IFB_ENG_ASSET_CSTR_SIZE};
        const u32 bytes_copied = sld::cstr_copy_from(&dst, path_src_cchar, IFB_ENG_ASSET_CSTR_SIZE);

        assert(
            bytes_copied >  0 &&
            bytes_copied <= IFB_ENG_ASSET_CSTR_SIZE
        );
    }
};

#endif //IFB_ENGINE_ASSET_CONFIG_HPP