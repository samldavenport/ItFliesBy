#ifndef   IFB_ENGINE_CONTEXT_HPP
#define   IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file-manager.hpp"
#include "ifb-engine-memory-manager.hpp"

namespace ifb::eng {

    struct context_t {
        stack_t           stack;
        file_manager_t*   file_mngr;
        memory_manager_t* memory_mngr;
    };

    IFB_ENG_INTERNAL void context_init_stack    (context_t* context, byte* stack_data, const u64 stack_size);
    IFB_ENG_INTERNAL void context_init_managers (context_t* context);


    template<typename struct_type_t>
    IFB_ENG_INTERNAL struct_type_t* context_stack_push_struct (context_t* context);
};


#endif  //IFB_ENGINE_CONTEXT_HPP