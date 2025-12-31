#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ifb-engine.hpp"
#include "core.hpp"
#include <stdio.h>

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct entity;
    struct entity_tag;
    struct entity_id;
    struct entity_manager;
    struct entity_sparse_set;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 ENTITY_TAG_SIZE = 32;    

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    entity_manager* entity_manager_init (const void* memory, const u32 size);
    entity_id       entity_create       (entity_manager* em, const cchar* tag_cstr);
    bool            entity_delete       (entity_manager* em, const entity_id id);
    entity_tag&     entity_get_tag      (entity_manager* em, const entity_id id);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_id {
        u32 val;

        constexpr explicit entity_id (const u32 v)           : val(v) { }
        constexpr          entity_id (void)                  : val(0) { }

        inline bool operator== (const entity_id& other)   { return(this->val == other.val); }
        friend bool operator== (entity_id a, entity_id b) { return(a.val == b.val);         }

        constexpr entity_id&
        operator=(
            const u32 v) {
            
            this->val = v;
            return(*this);
        }

        explicit constexpr
        operator bool() const {
            return(this->val != 0);
        }

        constexpr inline u32
        mask(
            const u32 m) const {
        
            const u32 result = (this->val & m); 
            return(result);
        }
    };

    struct entity_tag {
        cchar val[ENTITY_TAG_SIZE];

        explicit entity_tag(
            const cchar* cstr) {
            
            assert(cstr != NULL);

            (void)sprintf_s(
                &val[0], 
                ENTITY_TAG_SIZE,
                "%s",
                cstr
            );
        }

        inline entity_id
        to_id(
            void) {

            const u32 hash = hash_string(
                (char*)&this->val[0], // cstr
                ENTITY_TAG_SIZE       // length
            );

            entity_id id(hash);
            return(id);
        }
    };

    struct entity_manager {
        u32 capacity;
        u32 count;
        struct {
            entity_id*  id;
            entity_tag* tag;
        } data;
    };

    struct entity {
        entity_id   id;
        entity_tag* tag;
    };

    struct entity_sparse_array {
        u32 capacity;
        struct {
            entity_id* id;
            u32*       val;
        } array;

        explicit inline
        entity_sparse_array(
            const void* memory_ptr,
            const u32   memory_size) {

            const u32 entity_size = sizeof(entity_id) + sizeof(u32);

            assert(
                memory_ptr  != NULL &&
                memory_size >  entity_size
            );

            this->capacity  = (memory_size / entity_size);
            this->array.id  = (entity_id*)memory_ptr;
            this->array.val = (u32*)(((addr)memory_ptr) + (sizeof(entity_id) * capacity));

            assert(this->capacity != 0);
        }   

        inline bool
        lookup(
            const entity_id id,
            u32&            index) {

            bool found = false;

            for (
                index = id.mask(this->capacity - 1);
                index < this->capacity && !found;
                ++index) {

                const entity_id current_id = this->array.id[index];
                found = (current_id == id);
            }
            return(found);
        }
    };

    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        entity_tag tag("TEST TAG");
        entity_id  id = tag.to_id();

        const u32 index = id.mask(32);

        entity_sparse_array sparse_array(entity_memory, ENTITY_MEMORY_SIZE);     


        return(true);
    }
};

#endif //ENTITY_HPP