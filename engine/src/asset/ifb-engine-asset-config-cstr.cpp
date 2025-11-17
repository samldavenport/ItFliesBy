#pragma once

#include "ifb-engine-asset-config.hpp"

namespace ifb::eng {

    IFB_ENG_INTERNAL asset_config_string_t* 
    asset_config_cstr_arena_alloc(
        eng_mem_arena_t* arena) {

    }

    IFB_ENG_INTERNAL void 
    asset_config_cstr_update(
        asset_config_string_t* config_cstr,
        const cchar*         value) {

        sld::cstr_copy_from()
    }

};