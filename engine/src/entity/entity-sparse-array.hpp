#ifndef ENTITY_SPARSE_ARRAY_HPP
#define ENTITY_SPARSE_ARRAY_HPP

#include "ifb-engine.hpp"
#include "entity-id.hpp"

namespace ifb::eng {

    struct entity_sparse_entry {
        entity_id id;
        u32       val;
    };

    struct entity_sparse_array {

        // members
        u32 capacity;
        u32 count_current;
        u32 count_max;
        struct {
            entity_id* id;
            u32*       val;
        } array;

        // methods
        inline void init      (const void* memory_ptr, const u32 memory_size, const f32 max_load = 0.7);
        inline void validate  (void) const; 
        inline u32  mask      (void) const;
        inline bool lookup    (const entity_id id, u32& index) const;
        inline bool insert    (const entity_id id, const u32 val);
        inline void remove_at (const u32 index);
        inline void update_at (const u32 index, const u32 val);

        // operators
        inline entity_sparse_entry operator[](u32 index);
    };


    void inline
    entity_sparse_array::init(
        const void* memory_ptr,
        const u32   memory_size,
        const f32   max_load) {

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
    entity_sparse_array::validate(void) const {

        bool is_valid = true;
        is_valid &= (this->capacity      != 0);
        is_valid &= (this->array.id      != NULL);
        is_valid &= (this->array.val     != NULL);
        is_valid &= (this->count_current <= this->count_max);
        is_valid &= (this->count_max     != 0);
        assert(is_valid);
    }

    inline u32
    entity_sparse_array::mask(void) const {

        return(this->capacity - 1);
    }

    inline bool
    entity_sparse_array::lookup(
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
    entity_sparse_array::insert(
        const entity_id id,
        const u32       val) {

        bool did_insert = false;

        this->validate();
        if (this->count_current == this->count_max) {
            return(false);
        }

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
            ++this->count_current;
            did_insert = true;
            break;
        }

        return(did_insert);
    }

    inline void
    entity_sparse_array::remove_at(
        const u32 index) {

        this->validate();
        assert(index <= this->capacity);
        assert(this->array.id[index]);

        this->array.id[index] = 0;
        this->array.val       = 0;

        this->count_current = (this->count_current == 0)
            ? 0
            : this->count_current - 1;
    }

    inline void
    entity_sparse_array::update_at(
        const u32 index,
        const u32 val) {

        this->validate();
        assert(index <= this->capacity);

        this->array.val[index] = val;
    }

    inline entity_sparse_entry
    entity_sparse_array::operator[](
        u32 index) {

        this->validate();
        assert(index <= this->capacity);

        entity_sparse_entry entry;
        entry.id  = this->array.id  [index];
        entry.val = this->array.val [index];
        return(entry);
    }
};

#endif //ENTITY_SPARSE_ARRAY_HPP