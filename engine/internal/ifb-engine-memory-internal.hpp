#ifndef IFB_ENGINE_MEMORY_INTERNAL_HPP
#define IFB_ENGINE_MEMORY_INTERNAL_HPP

#include <sld-memory.hpp>
#include <sld-arena-allocator.hpp>
#include <sld-arena.hpp>

#include "ifb-engine-memory.hpp"

namespace ifb {

    constexpr u64 ENG_MEM_SIZE_RES_CORE    = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_RES_CORE); 
    constexpr u64 ENG_MEM_SIZE_RES_FILE    = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_RES_FILE); 
    constexpr u64 ENG_MEM_SIZE_RES_ASSET   = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_RES_ASSET); 
    constexpr u64 ENG_MEM_SIZE_RES_GUI     = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_RES_GUI);

    constexpr u64 ENG_MEM_SIZE_ARENA_CORE  = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_ARENA_CORE); 
    constexpr u64 ENG_MEM_SIZE_ARENA_FILE  = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_ARENA_FILE);
    constexpr u64 ENG_MEM_SIZE_ARENA_ASSET = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_ARENA_ASSET);
    constexpr u64 ENG_MEM_SIZE_ARENA_GUI   = sld::size_kilobytes (IFB_ENG_MEM_SIZE_KB_ARENA_GUI);

    using eng_mem_error_s32_t   = eng_error_s32_t; 
    using eng_mem_arena_t       = sld::arena_t; 
    using eng_mem_alctr_arena_t = sld::arena_allocator_t;

    static eng_mem_alctr_arena_t _alctr_arena_core;
    static eng_mem_alctr_arena_t _alctr_arena_file;
    static eng_mem_alctr_arena_t _alctr_arena_asset;
    static eng_mem_alctr_arena_t _alctr_arena_gui;

    struct eng_mem_arena_alctrs_t {
        eng_mem_alctr_arena_t* core;
        eng_mem_alctr_arena_t* file;
        eng_mem_alctr_arena_t* asset;
        eng_mem_alctr_arena_t* gui;
    };

    struct eng_mem_mngr_t {
        eng_mem_arena_alctrs_t arena_allocators;
        eng_mem_error_s32_t    last_error;
    };

    IFB_ENG_INTERNAL void              eng_mem_mngr_startup          (void);
    
    IFB_ENG_INTERNAL eng_mem_arena_t*  eng_mem_arena_commit_core     (void);   
    IFB_ENG_INTERNAL eng_mem_arena_t*  eng_mem_arena_commit_file     (void);   
    IFB_ENG_INTERNAL eng_mem_arena_t*  eng_mem_arena_commit_asset    (void);
    
    IFB_ENG_INTERNAL void              eng_mem_arena_decommit_core   (eng_mem_arena_t* arena);   
    IFB_ENG_INTERNAL void              eng_mem_arena_decommit_file   (eng_mem_arena_t* arena);   
    IFB_ENG_INTERNAL void              eng_mem_arena_decommit_asset  (eng_mem_arena_t* arena);
};


#endif // IFB_ENGINE_MEMORY_INTERNAL_HPP