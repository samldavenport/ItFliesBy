#ifndef IFB_ENGINE_ASSET_CONFIG_HPP
#define IFB_ENGINE_ASSET_CONFIG_HPP

#include <sld-arena.hpp>
#include "ifb-engine.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    constexpr cchar ENG_ASSET_CONFIG_NODE_NAME_TEXT  [] = "text";
    constexpr cchar ENG_ASSET_CONFIG_NODE_NAME_IMAGE [] = "image";
    constexpr cchar ENG_ASSET_CONFIG_NODE_NAME_SOUND [] = "sound";
    constexpr cchar ENG_ASSET_CONFIG_NODE_NAME_FONT  [] = "font";
    constexpr cchar ENG_ASSET_CONFIG_DEFAULT_CONFIG  [] = 
        "<ifb-assets>"
            "<text path=\"../assets/text\"></text>"
            "<image path=\"../assets/image\"></image>"
            "<sound path=\"../assets/sound\"></sound>"
            "<font path=\"../assets/font\"></font>"
        "</ifb-assets>";

    struct eng_asset_config_cstr_t;
    struct eng_asset_config_file_t;
    struct eng_asset_config_file_node_t;
    struct eng_asset_config_editor_context_t;

    IFB_ENG_INTERNAL eng_asset_config_editor_context_t* asset_config_editor_context_init                  (eng_mem_arena_t* arena);
    IFB_ENG_INTERNAL eng_asset_config_file_node_t*      asset_config_editor_context_add_text              (eng_asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL eng_asset_config_file_node_t*      asset_config_editor_context_add_image             (eng_asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL eng_asset_config_file_node_t*      asset_config_editor_context_add_sound             (eng_asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL eng_asset_config_file_node_t*      asset_config_editor_context_add_font              (eng_asset_config_editor_context_t* editor_context, eng_mem_arena_t* arena, const cchar* asset_name, const cchar* asset_path);
    IFB_ENG_INTERNAL void                               asset_config_editor_context_update_file_node_name (eng_asset_config_file_node_t*      file_node,      const cchar*     asset_name);
    IFB_ENG_INTERNAL void                               asset_config_editor_context_update_file_node_path (eng_asset_config_file_node_t*      file_node,      const cchar*     asset_path);
    IFB_ENG_INTERNAL void                               asset_config_editor_delete_file_node              (eng_asset_config_file_node_t*      file_node);

    struct eng_asset_config_file_t {
        eng_asset_cstr_t* name;
        eng_asset_cstr_t* path;
    };

    struct eng_asset_config_file_list_t {
        eng_asset_config_file_node_t* first;
        eng_asset_config_file_node_t* last;
    };

    struct eng_asset_config_editor_context_t {
        eng_asset_config_cstr_t* path;
        struct {
            eng_asset_config_file_list_t text;
            eng_asset_config_file_list_t image;
            eng_asset_config_file_list_t sound;
            eng_asset_config_file_list_t font;
        } file_list;
    };

    struct eng_asset_config_file_node_t {
        eng_asset_cstr_t*              name;
        eng_asset_cstr_t*              path;
        eng_asset_config_file_node_t*  next;
        eng_asset_config_file_node_t*  prev;
    };

    
    IFB_ENG_INTERNAL_INLINE eng_asset_config_file_node_t* 
    asset_config_arena_alloc_file_node(eng_mem_arena_t* arena) {

        auto file_node    = sld::arena_push_struct<eng_asset_config_file_node_t> (arena);
        auto string_array = sld::arena_push_struct<eng_asset_cstr_t>             (arena, 2);
        
        assert(
            file_node    != NULL &&
            string_array != NULL
        );

        file_node->name = &string_array[0];
        file_node->path = &string_array[1];
        file_node->next = NULL;
        file_node->prev = NULL;
        return(file_node);
    };

    IFB_ENG_INTERNAL_INLINE eng_asset_config_file_node_t*
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

        eng_asset_config_file_node_t* node = asset_config_arena_alloc_file_node(arena);
        asset_config_file_node_update_name (node, asset_name);
        asset_config_file_node_update_path (node, asset_path);

        return(node);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_file_node_update_name(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  name_src_cchar) {

        assert(
            file_node       != NULL &&
            file_node->name != NULL &&
            name_src_cchar  != NULL
        );

        eng_asset_cstr_t* name = file_node->name;
        cstr_t    dst          = { name->chars, IFB_ENG_ASSET_CSTR_SIZE};
        const u32 bytes_copied = sld::cstr_copy_from(&dst, name_src_cchar, IFB_ENG_ASSET_CSTR_SIZE);

        assert(
            bytes_copied >  0 &&
            bytes_copied <= IFB_ENG_ASSET_CSTR_SIZE
        );

        eng_asset_name_sanitize(1, file_node->name);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_file_list_add_node(
        eng_asset_config_file_list_t* file_list,
        eng_asset_config_file_node_t* file_node) {

        assert(file_list != NULL && file_node != NULL);

        if (file_list->first == NULL) {
            assert(file_list->last != NULL);

            file_node->next = NULL;
            file_node->prev = NULL;
            file_list->first = file_node;
            file_list->last  = file_node;
            return;
        }

        assert(file_list->first != NULL && file_list->last != NULL);

        eng_asset_config_file_node_t* old_last = file_list->last;

        file_node->next = NULL;
        file_node->prev = old_last;
        old_last->next  = file_node;
        file_list->last = file_node;
        assert(old_last->prev != NULL);
    }

    IFB_ENG_INTERNAL_INLINE void
    asset_config_file_node_update_path(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  path_src_cchar) {

        assert(
            file_node       != NULL &&
            file_node->path != NULL &&
            path_src_cchar  != NULL
        );

        eng_asset_cstr_t* path = file_node->path;
        cstr_t    dst          = { path->chars, IFB_ENG_ASSET_CSTR_SIZE};
        const u32 bytes_copied = sld::cstr_copy_from(&dst, path_src_cchar, IFB_ENG_ASSET_CSTR_SIZE);

        assert(
            bytes_copied >  0 &&
            bytes_copied <= IFB_ENG_ASSET_CSTR_SIZE
        );
    }
};

#endif //IFB_ENGINE_ASSET_CONFIG_HPP