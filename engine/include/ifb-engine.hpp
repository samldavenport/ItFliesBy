#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>
#include <sld-stack.hpp>
#include "ifb-engine-config.hpp"

#define IFB_ENG_API                  __declspec(dllexport)
#define IFB_ENG_API_INLINE           inline
#define IFB_ENG_INLINE               inline
#define IFB_ENG_GLOBAL               static
#define IFB_ENG_LOCAL                static
#define IFB_ENG_INTERNAL             static
#define IFB_ENG_INTERNAL_TEMPLATE(t) template<typename t> static
#define IFB_ENG_INTERNAL_INLINE      static inline

using namespace sld;

#define for_count_u32(index, count) for (u32 index = 0; index < count; ++index)

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct error  : s32_t { };
    struct handle : u32_t { };
    struct flags  : u32_t { };
    struct context;
    struct memory_map;
    struct singleton_stack;
    struct virtual_memory;
    struct memory;
    struct engine_config;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------
    
    IFB_ENG_API context* context_create      (const engine_config* config);
    IFB_ENG_API bool     context_startup     (context* ctx);
    IFB_ENG_API bool     context_shutdown    (context* ctx);
    IFB_ENG_API bool     context_update      (context* ctx);
    IFB_ENG_API bool     context_render      (context* ctx);
    IFB_ENG_API bool     context_should_quit (context* ctx);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct memory {
        union {
            void* as_ptr;
            byte* as_bytes;
            addr  as_addr;
        } start;
        u64  size;

        inline bool
        is_valid(void) {
            return(
                this->start.as_ptr != NULL &&
                this->size         != 0
            );
        }
    };

    struct virtual_memory {
        u32 granularity;
        u32 page_size;
        struct {
            memory entities;
            memory graphics;
            memory arenas;
        } reservation;
    };

    struct memory_map {
        stack          singleton_stack;
        virtual_memory os_virtual_memory;
    };

    struct engine_config {
        memory_map mem_map;
    };
};

#endif //IFB_ENGINE_HPP