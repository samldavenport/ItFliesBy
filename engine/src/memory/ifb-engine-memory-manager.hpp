#ifndef IFB_ENGINE_MEMORY_MANAGER_HPP
#define IFB_ENGINE_MEMORY_MANAGER_HPP

#include <sld-memory.hpp>

#include "ifb-engine.hpp"


namespace ifb::eng {

    struct memory_manager_t {
        memory_t os_reserved;
        memory_t file_io;
    };


};

#endif //IFB_ENGINE_MEMORY_MANAGER_HPP