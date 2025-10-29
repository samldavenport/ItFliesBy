#ifndef IFB_ENGINE_ASSET_CONFIG_HPP
#define IFB_ENGINE_ASSET_CONFIG_HPP

#include <sld-arena.hpp>
#include <sld-double-linked-list.hpp>
#include "ifb-engine.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-string.hpp"
#include "ifb-engine-file.hpp"

using namespace ifb;
namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

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

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct asset_config_asset_list_t;
    struct asset_config_asset_t;
    struct asset_config_asset_data_t;
    struct asset_config_context_t;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // context
    IFB_ENG_INTERNAL bool                 asset_config_context_is_valid       (asset_config_context_t& context);
    IFB_ENG_INTERNAL void                 asset_config_context_create         (asset_config_context_t& context);
    IFB_ENG_INTERNAL void                 asset_config_context_destroy        (asset_config_context_t& context);
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_context_add_text_node  (asset_config_context_t& context, const cchar* name, const cchar* path); 
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_context_add_image_node (asset_config_context_t& context, const cchar* name, const cchar* path);
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_context_add_sound_node (asset_config_context_t& context, const cchar* name, const cchar* path);
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_context_add_font_node  (asset_config_context_t& context, const cchar* name, const cchar* path);

    // config nodes
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_node_arena_alloc       (eng_mem_arena_t* arena);
    IFB_ENG_INTERNAL void                 asset_config_node_init              (asset_config_asset_t* node, const cchar* name, const cchar* path);
    IFB_ENG_INTERNAL void                 asset_config_node_update_name       (asset_config_asset_t* node, const cchar* name);
    IFB_ENG_INTERNAL void                 asset_config_node_update_path       (asset_config_asset_t* node, const cchar* path);

    // config list
    IFB_ENG_INTERNAL asset_config_asset_list_t* asset_config_list_arena_alloc       (eng_mem_arena_t* arena, const u32 count = 1);
    IFB_ENG_INTERNAL void                 asset_config_list_remove_node       (asset_config_asset_list_t* list, asset_config_asset_t* node);
    IFB_ENG_INTERNAL void                 asset_config_list_add_existing_node (asset_config_asset_list_t* list, asset_config_asset_t* node);
    IFB_ENG_INTERNAL asset_config_asset_t* asset_config_list_add_new_node      (asset_config_asset_list_t* list, arena_t* arena, const cchar* name, const cchar* path);


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct asset_config_asset_data_t {
        string_c32_t* name;
        string_c32_t* path;
    };  

    struct asset_config_asset_t      : sld::dl_node_t<asset_config_asset_data_t> { }; 
    struct asset_config_asset_list_t : sld::dl_list_t<asset_config_asset_data_t> { };

    struct asset_config_context_t {
        struct {
            asset_config_asset_list_t* text;
            asset_config_asset_list_t* image;
            asset_config_asset_list_t* sound;
            asset_config_asset_list_t* font;
            asset_config_asset_list_t* deleted;
        } node_list;
        arena_allocator_t* arena_allocator;
        arena_t*           active_arena;
    };
};

#endif //IFB_ENGINE_ASSET_CONFIG_HPP