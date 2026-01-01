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
        inline bool operator== (const u32 other) {return(this->val == other);}
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

    struct entity_sparse_entry {
        entity_id id;
        u32       val;
    };

    struct entity_sparse_array {
        u32 capacity;
        u32 count_current;
        u32 count_max;
        struct {
            entity_id* id;
            u32*       val;
        } array;

        void inline
        init(
            const void* memory_ptr,
            const u32   memory_size,
            const f32   max_load = 0.7) {

            const u32 entity_size = sizeof(entity_id) + sizeof(u32);

            assert(
                memory_ptr  != NULL        &&
                memory_size >  entity_size &&
                max_load    <= 1.0f
            );

            this->capacity      = (memory_size / entity_size);
            this->count_current = 0;
            this->count_max     = (u32)(((f32)this->capacity) * max_load);
            this->array.id      = (entity_id*)memory_ptr;
            this->array.val     = (u32*)(((addr)memory_ptr) + (sizeof(entity_id) * capacity));

            assert(this->capacity != 0);
        }   

        void inline
        validate(void) const {

            bool is_valid = true;
            is_valid &= (this->capacity      != 0);
            is_valid &= (this->array.id      != NULL);
            is_valid &= (this->array.val     != NULL);
            is_valid &= (this->count_current <= this->count_max);
            is_valid &= (this->count_max     != 0);
            assert(is_valid);
        }

        inline u32
        mask(void) const {

            return(this->capacity - 1);
        }

        inline bool
        lookup(
            const entity_id id,
            u32&            index) const {

            assert(id);
            this->validate();

            const u32 mask = (this->capacity - 1);

            index = (id.val & mask);

            bool found = false;

            for (
                u32 probe = 0;
                probe < this->capacity;
                ++probe) {

                const entity_id current_id = this->array.id[index];
                
                found = (current_id == id); 

                if (!current_id) break; // slot is empty
                if (found)       break; // found id

                // not found yet, increase the index with wrapping
                index = (index + 1) & mask; 
            }

            return(found);
        }

        inline bool
        insert(
            const entity_id id,
            const u32       val) {

            bool did_insert = false;

            this->validate();

            u32 index;
            const bool exists = this->lookup(id, index); 
            assert(id && !exists);

            const u32 mask = this->mask();
            index = (id.val & mask);
            for (
                u32 probe = 0;
                probe < this->capacity;
                ++probe) {

                // if this slot is occupied, go to the next one
                const entity_id current_id = this->array.id[index]; 
                if (current_id) {
                    index = (index + 1) & mask; 
                    continue;
                }

                // found an unoccupied cell, insert the data
                this->array.id  [index] = id;
                this->array.val [index] = val;
                did_insert = true;
                break;
            }

            return(did_insert);
        }

        inline entity_sparse_entry
        operator[](
            u32 index) {

            this->validate();
            assert(index <= this->capacity);

            entity_sparse_entry entry;
            entry.id  = this->array.id  [index];
            entry.val = this->array.val [index];
            return(entry);
        }
    };

    constexpr u32 ENTITY_MEMORY_SIZE = size_kilobytes(64); 
    static byte entity_memory[ENTITY_MEMORY_SIZE];

    inline bool
    entity_test(
        void) {

        entity_tag tag("TEST TAG");
        entity_id  id = tag.to_id();

        entity_sparse_array sparse_array;
        sparse_array.init(entity_memory, ENTITY_MEMORY_SIZE);

        
        bool result = false;

        u32 index = 0;
        result = sparse_array.lookup(id, index); 
        assert(!result);

        result = sparse_array.insert(id, 5);
        assert(result);

        result = sparse_array.lookup(id, index);
        assert(result);

        entity_sparse_entry entry = sparse_array[index];
        assert(
            entry.id.val == id.val &&
            entry.val    == 5 
        );

        return(true);
    }
};

#endif //ENTITY_HPP