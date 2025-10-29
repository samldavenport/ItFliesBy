#pragma once

#include "ifb-engine.hpp"

namespace ifb::eng {

    IFB_ENG_API bool core_startup     (void);
    IFB_ENG_API bool core_shutdown    (void);
    IFB_ENG_API bool core_update      (void);
    IFB_ENG_API bool core_render      (void);
    IFB_ENG_API bool core_should_quit (void);
};