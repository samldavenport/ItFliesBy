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

        inline bool operator== (const entity_id& other) { return(this->val == other.val); }
        friend bool operator== (entity_id a, entity_id b) { return(a.val == b.val); }

        constexpr entity_id&
        operator=(
            const u32 v) {
            
            this->val = v;
            return(*this);
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


    inline void
    entity_test(
        void) {

        entity_tag tag("TEST TAG");
        entity_id  id = tag.to_id();
    }
};

#endif //ENTITY_HPP