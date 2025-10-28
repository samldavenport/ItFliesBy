#pragma once

#include <sld-os.hpp>
#include <sld-cstr.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-string.hpp"

namespace ifb {


    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------


    using eng_core_input_keyboard_t  = sld::input_keyboard_t;
    
\
    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    //-------------------------------------------------------------------
    // SINGLETONS
    //-------------------------------------------------------------------

    static eng_core_input_keyboard_t _eng_core_input_keyboard;
    static eng_core_monitor_table_t  _eng_core_monitor_table;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

};
