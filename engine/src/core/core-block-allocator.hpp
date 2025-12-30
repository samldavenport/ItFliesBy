#ifndef IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP
#define IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    struct block_memory {
        block_memory* next;
        block_memory* prev;
    };

    struct block_allocator {

        // members
        block_memory* free_blocks;
        block_memory* used_blocks;
        u32           size;
        u32           stride;

        // methods
        inline static block_allocator* init      (void* memory, const u32 size, const u32 stride);
        inline        void*            alloc     (void);
        inline        void             free      (void* memory);
        inline        u32              size_free (void);
        inline        u32              size_used (void);
        inline        void             validate  (void);
        inline        void             reset     (void);
    };


    inline block_allocator*
    block_allocator::init(
        void*     memory,
        const u32 size,
        const u32 stride) {

        constexpr u32 size_allocator    = sizeof(block_allocator);
        const u32     size_block        = sizeof(block_memory) + size_round_up_pow2(stride);
        const u32     size_block_memory = (size - size_allocator);
        const u32     size_min          = (size_allocator + size_block);

        assert(
            memory != NULL     &&
            size   >= size_min &&
            stride <= size     &&
            stride >  0
        );

        block_allocator* allocator   = (block_allocator*)memory;
        const addr       block_start = (addr)memory + size_allocator;
        const u32        block_count = (size_block_memory / size_block);
        assert(block_count > 0);

        block_memory* block_current = NULL;
        block_memory* block_prev    = (block_memory*)block_start;
        block_prev->prev = NULL;
        for (
            u32 block_index = 0;
            block_index < block_count;
            ++block_index) {
            
            const u32  block_offset = (block_index * size_block);
            const addr block_addr   = (block_start + block_offset);
            block_current = (block_memory*)block_addr; 

            block_current->next = NULL;
            block_current->prev = block_prev;
            block_prev->next    = block_current;
        }

        allocator->free_blocks = (block_memory*)block_start;
        allocator->used_blocks = NULL;
        allocator->stride      = stride;
        allocator->size        = size; 
        return(allocator);
    }

    inline void*
    block_allocator::alloc(
        void) {

        this->validate();

        block_memory* block = this->free_blocks;
        if (!block) return(block);

        this->free_blocks = block->next;
        block->next = this->used_blocks;
        this->used_blocks = block;

        const addr mem_addr = ((addr)block) + sizeof(block_memory);
        void*      mem_ptr  = (void*)mem_addr;
        return(mem_ptr); 
    }

    inline void
    block_allocator::free(
        void* memory) {

        this->validate();

        const addr allocator_size  = sizeof(block_allocator);
        const addr allocator_start = ((addr)this);
        const addr mem_addr        = (addr)memory;
        const u32  block_size      = sizeof(block_memory) + this->stride; 
        const addr block_first     = allocator_start + sizeof(block_allocator);
        const addr block_last      = allocator_start + (this->size - block_size); 
        const addr block_start     = mem_addr - block_size; 
        const addr block_offset    = block_start - (allocator_start + allocator_size); 

        assert(
            memory       != NULL        &&
            block_start  >= block_first &&
            block_start  <= block_last  &&
            (block_offset % block_size) == 0
        );


        block_memory* block      = (block_memory*)(block_start);
        block_memory* block_prev = (block_memory*)(block_start - block_size);

    }
    
    inline u32
    block_allocator::size_free(
        void) {

    }

    inline u32
    block_allocator::size_used(
        void) {

    }

    inline void
    block_allocator::validate(
        void) {

        assert(
            (this->free_blocks != NULL || this->used_blocks != NULL) &&
            this->size > 0 &&
            this->stride <= this->size
        );
    }

    inline void
    block_allocator::reset(
        void) {

    }
};

#endif //IFB_ENG_CORE_BLOCK_ALLOCATOR_HPP