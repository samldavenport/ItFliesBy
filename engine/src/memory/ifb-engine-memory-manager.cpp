#pragma once

#include "ifb-engine-memory-internal.hpp"

using namespace sld;

namespace ifb {

    static eng_mem_mngr_t _mem_mngr;

    IFB_ENG_INTERNAL void
    eng_mem_mngr_startup(
        void) {
        
        _mem_mngr.arena_allocators.core  = &_alctr_arena_core;
        _mem_mngr.arena_allocators.file  = &_alctr_arena_file;
        _mem_mngr.arena_allocators.asset = &_alctr_arena_asset;
        _mem_mngr.arena_allocators.gui   = &_alctr_arena_gui;

        sld::arena_allocator_reserve_os_memory (_mem_mngr.arena_allocators.core,  ENG_MEM_SIZE_RES_CORE,  ENG_MEM_SIZE_ARENA_CORE);
        sld::arena_allocator_reserve_os_memory (_mem_mngr.arena_allocators.file,  ENG_MEM_SIZE_RES_FILE,  ENG_MEM_SIZE_ARENA_FILE);
        sld::arena_allocator_reserve_os_memory (_mem_mngr.arena_allocators.asset, ENG_MEM_SIZE_RES_ASSET, ENG_MEM_SIZE_ARENA_ASSET);
        sld::arena_allocator_reserve_os_memory (_mem_mngr.arena_allocators.gui,   ENG_MEM_SIZE_RES_GUI,   ENG_MEM_SIZE_ARENA_GUI);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_core(
        void) {

        eng_mem_arena_t* arena = arena_allocator_commit(_mem_mngr.arena_allocators.core); 
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_file(
        void) {

        eng_mem_arena_t* arena = arena_allocator_commit(_mem_mngr.arena_allocators.file); 
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_asset(
        void) {

        eng_mem_arena_t* arena = arena_allocator_commit(_mem_mngr.arena_allocators.asset); 
        return(arena);
    }
  
    IFB_ENG_INTERNAL void
    eng_mem_arena_decommit_core(
        eng_mem_arena_t* arena) {

        arena_allocator_decommit(_mem_mngr.arena_allocators.core, arena);
    }

    IFB_ENG_INTERNAL void
    eng_mem_arena_decommit_file(
        eng_mem_arena_t* arena) {

        arena_allocator_decommit(_mem_mngr.arena_allocators.file, arena);
    }

    IFB_ENG_INTERNAL void
    eng_mem_arena_decommit_asset(
        eng_mem_arena_t* arena) {

        arena_allocator_decommit(_mem_mngr.arena_allocators.asset, arena);
    }

};