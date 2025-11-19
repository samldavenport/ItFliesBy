#ifndef IFB_ENGINE_CORE_CONTEXT_HPP
#define IFB_ENGINE_CORE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file-manager.hpp"
#include "ifb-engine-memory-manager.hpp"

#define IFB_ENGINE_CORE_CONTEXT_STACK_SIZE_KB 64

namespace ifb::eng {

    constexpr u64 CORE_CONTEXT_STACK_SIZE = size_kilobytes(IFB_ENGINE_CORE_CONTEXT_STACK_SIZE_KB);

    struct core_context_managers_t {
        memory_manager_t* memory;
        file_manager_t*   file;
    };

    struct core_context_t {
        stack_t                  stack;
        core_context_managers_t* managers;        
    };

    IFB_ENG_GLOBAL core_context_t _core_context;
    IFB_ENG_GLOBAL byte           _core_context_stack_data[CORE_CONTEXT_STACK_SIZE];


};

#endif //IFB_ENGINE_CORE_CONTEXT_HPP