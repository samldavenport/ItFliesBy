#pragma once

#include "memory.hpp"

namespace ifb::eng {

    void
    arena::validate(
        void) {

        const u32 arena_size = memory_manager::os_granularity();

        assert(
            this->_position < arena_size
        );
    }

    void
    arena::reset(
        void) {

        this->validate();

        this->_position = 0;
        this->_save     = 0;

    }

    u32
    arena::save(
        void) {

        this->validate();
        assert(this->_save = 0);
        this->_save = this->_position;
    }

    void
    arena::revert(
        const u32 save) {

        this->validate();
        assert(save == this->_save);
        this->_position = this->_save;
    }

    void*
    arena::push(
        const u32 size,
        const u32 alignment) {

        const u32 size_aligned = size_is_pow_2(alignment)
            ? size_align_pow_2 (size, alignment)
            : size_align       (size, alignment);

        const u32  new_position = (this->_position + size_aligned);
        const u32  arena_size   = memory_manager::os_granularity(); 
        const bool can_push     = (new_position < arena_size);
        this->validate();

        void* mem = NULL;
        if (can_push) {
            
            mem = (void*)(((addr)this) + this->_position);
            this->_position = new_position;
        }
        return(mem);
    }

    template<typename t> t*
    arena::push_struct(
        const u32 count) {

        assert(count != 0);
        const u32 size = (sizeof(t) * count);
        t* mem = (t*)this->push(size);
    }
};