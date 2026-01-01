#ifndef ENTITY_SPARSE_ARRAY_HPP
#define ENTITY_SPARSE_ARRAY_HPP

#include "ifb-engine.hpp"
#include "entity-id.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_sparse_entry {
        entity_id id;
        u32       val;
    };

    class entity_sparse_array {

    private:

        // members
        u32 _capacity;
        u32 _count_current;
        u32 _count_max;
        struct {
            entity_id* id;
            u32*       val;
        } _sparse_data;

    public:

        // constructor
        explicit inline
        entity_sparse_array (
            const void* memory_ptr,
            const u32   memory_size,
            const f32   max_load = 0.7
        );

        // methods
        inline void validate  (void) const; 
        inline u32  mask      (void) const;
        inline bool lookup    (const entity_id id, u32& index) const;
        inline bool insert    (const entity_id id, const u32 val);
        inline void remove_at (const u32 index);
        inline void update_at (const u32 index, const u32 val);

        // operators
        inline entity_sparse_entry operator[](u32 index);
    };

    //-------------------------------------------------------------------
    // CONSTRUCTOR
    //-------------------------------------------------------------------

    inline entity_sparse_array::
    entity_sparse_array(
        const void* memory_ptr,
        const u32   memory_size,
        const f32   max_load) {

        const u32 entity_size = sizeof(entity_id) + sizeof(u32);

        assert(
            memory_ptr  != NULL        &&
            memory_size >  entity_size &&
            max_load    <= 1.0f
        );

        this->_capacity        = (memory_size / entity_size);
        this->_count_current   = 0;
        this->_count_max       = (u32)(((f32)this->_capacity) * max_load);
        this->_sparse_data.id  = (entity_id*)memory_ptr;
        this->_sparse_data.val = (u32*)(((addr)memory_ptr) + (sizeof(entity_id) * this->_capacity));

        assert(this->_capacity != 0);
    }   

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    void inline entity_sparse_array::
    validate(void) const {

        bool is_valid = true;
        is_valid &= (this->_capacity      != 0);
        is_valid &= (this->_sparse_data.id      != NULL);
        is_valid &= (this->_sparse_data.val     != NULL);
        is_valid &= (this->_count_current <= this->_count_max);
        is_valid &= (this->_count_max     != 0);
        assert(is_valid);
    }

    inline u32 entity_sparse_array::
    mask(void) const {

        return(this->_capacity - 1);
    }

    inline bool entity_sparse_array::
    lookup(
        const entity_id id,
        u32&            index) const {

        assert(id);
        this->validate();

        const u32 mask = (this->_capacity - 1);

        index = (id.val & mask);

        bool found = false;

        for (
            u32 probe = 0;
            probe < this->_capacity;
            ++probe) {

            const entity_id current_id = this->_sparse_data.id[index];
            
            found = (current_id == id); 

            if (!current_id) break; // slot is empty
            if (found)       break; // found id

            // not found yet, increase the index with wrapping
            index = (index + 1) & mask; 
        }

        return(found);
    }

    inline bool
    entity_sparse_array::
    insert(
        const entity_id id,
        const u32       val) {

        bool did_insert = false;

        this->validate();
        if (this->_count_current == this->_count_max) {
            return(false);
        }

        u32 index;
        const bool exists = this->lookup(id, index); 
        assert(id && !exists);

        const u32 mask = this->mask();
        index = (id.val & mask);
        for (
            u32 probe = 0;
            probe < this->_capacity;
            ++probe) {

            // if this slot is occupied, go to the next one
            const entity_id current_id = this->_sparse_data.id[index]; 
            if (current_id) {
                index = (index + 1) & mask; 
                continue;
            }

            // found an unoccupied cell, insert the data
            this->_sparse_data.id  [index] = id;
            this->_sparse_data.val [index] = val;
            ++this->_count_current;
            did_insert = true;
            break;
        }

        return(did_insert);
    }

    inline void
    entity_sparse_array::
    remove_at(
        const u32 index) {

        this->validate();
        assert(index <= this->_capacity);
        assert(this->_sparse_data.id[index]);

        this->_sparse_data.id[index] = 0;
        this->_sparse_data.val       = 0;

        this->_count_current = (this->_count_current == 0)
            ? 0
            : this->_count_current - 1;
    }

    inline void
    entity_sparse_array::
    update_at(
        const u32 index,
        const u32 val) {

        this->validate();
        assert(index <= this->_capacity);

        this->_sparse_data.val[index] = val;
    }

    //-------------------------------------------------------------------
    // OPERATORS
    //-------------------------------------------------------------------

    inline entity_sparse_entry
    entity_sparse_array::operator[](
        u32 index) {

        this->validate();
        assert(index <= this->_capacity);

        entity_sparse_entry entry;
        entry.id  = this->_sparse_data.id  [index];
        entry.val = this->_sparse_data.val [index];
        return(entry);
    }
};

#endif //ENTITY_SPARSE_ARRAY_HPP