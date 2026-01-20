#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    class memory_manager;
    struct arena;
    struct stack_allocator;
    struct block_allocator;
    struct arena_allocator;
    struct arena_handle;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    // map
    IFB_ENG_INTERNAL           void memory_manager_init                 (memory_map* const mem_map);
    IFB_ENG_INTERNAL           void memory_manager_destroy              (void);
    IFB_ENG_INTERNAL            u32 memory_manager_align_to_page        (const u32 size);
    IFB_ENG_INTERNAL            u32 memory_manager_align_to_granularity (const u32 size);

    // arena
    IFB_ENG_INTERNAL           bool arena_alloc                     (arena_handle& arena_handle);
    IFB_ENG_INTERNAL           void arena_validate                  (arena_handle& const arena_hnd);
    IFB_ENG_INTERNAL           void arena_free                      (arena_handle& const arena_hnd);
    IFB_ENG_INTERNAL           void arena_reset                     (arena_handle& const arena_hnd);
    IFB_ENG_INTERNAL            u32 arena_save                      (arena_handle& const arena_hnd);
    IFB_ENG_INTERNAL           void arena_revert                    (arena_handle& const arena_hnd, const u32 save);
    IFB_ENG_INTERNAL          void* arena_push                      (arena_handle& const arena_hnd, const u32 size, const u32 alignment = 0);
    IFB_ENG_INTERNAL_TEMPLATE(t) t* arena_push_struct               (arena_handle& const arena_hnd, const u32 count = 1);


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct arena {
        
        arena* next;
        arena* prev;
        u32    index;
        u32    position;
        u32    save;

        void  validate (void);
        void  reset    (void);
        u32   save     (void);
        void  revert   (const u32 save);
        void* push     (const u32 size, const u32 alignment = 0);

        template<typename t>
        t* push_struct(const u32 count = 1);
    };

    struct block_allocator : memory {
        u32 block_capacity;
        u32 block_count;
        u32 block_size;
    };

    struct stack_allocator {
        virtual_memory* vmem;
        u32             offset;
        u32             size;
        u32             granularity;
        u32             page_capacity;
        u32             page_count;
        u32             page_position;
    };

    struct arena_allocator {
        addr start;
        u32  arena_size;
        u32  arena_count_total;
        u32  arena_count_used;

        inline void
        validate(void) {

            const bool is_valid = (
                this->start             != 0 &&
                this->arena_size        != 0 &&
                this->arena_count_total != 0 &&
                this->arena_count_used  <= this->arena_count_total
            );
            assert(is_valid);
        }
    };

    class memory_manager {

    private:

        static memory_map*      _mem_map;
        static arena_allocator* _arena_allocator;

    public:

        static void   startup                 (void);
        static void   shutdown                (void);
        static arena* arena_alloc             (void);
        static void   arena_free              (arena** arena);
        static void*  virtual_memory_commit   (virtual_memory* const vmem, const u32 offset, const u32 size);
        static void   virtual_memory_decommit (virtual_memory* const vmem, const u32 offset, const u32 size);
        
        template<typename t>
        static t* singleton_alloc (const u32 count = 1);

        static inline const u32 os_granularity          (void)           { return(_mem_map->os_virtual_memory.granularity);                         }
        static inline const u32 os_page_size            (void)           { return(_mem_map->os_virtual_memory.page_size);                           }
        static inline const u32 align_to_os_granularity (const u32 size) { return(size_align_pow_2(size, _mem_map->os_virtual_memory.granularity)); }
        static inline const u32 align_to_os_page_size   (const u32 size) { return(size_align_pow_2(size, _mem_map->os_virtual_memory.page_size));   }
    };
};

#endif //MEMORY_HPP