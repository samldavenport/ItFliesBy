#ifndef IFB_ENGINE_ENTITY_HPP
#define IFB_ENGINE_ENTITY_HPP

#include <stdio.h>

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct entity;
    struct entity_id;
    struct entity_tag;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------
    
    constexpr u32 ENTITY_ID_INVALID = 0;
    constexpr u32 ENTITY_TAG_SIZE   = 32;    

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct entity_id {
        u32 val;

        constexpr explicit entity_id (const u32 v) : val(v) { }
        constexpr          entity_id (void)        : val(0) { }

        inline bool operator== (const entity_id&  other)  { return(this->val == other.val); }
        inline bool operator== (const u32& other)         { return(this->val == other);     }
        inline bool operator== (const s32& other)         { return(this->val == other);     }
        friend bool operator== (entity_id a, entity_id b) { return(a.val == b.val);         }

        constexpr entity_id&
        operator=(
            const u32 v) {
            
            this->val = v;
            return(*this);
        }

        constexpr entity_id&
        operator=(
            const s32 v) {
            
            this->val = (u32)v;
            return(*this);
        }

        explicit constexpr
        operator bool() const {
            return(this->val != 0);
        }
    };
    struct entity_tag {

        // members
        cchar val[ENTITY_TAG_SIZE];

        // methods
        inline
        entity_tag::entity_tag(
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
        entity_tag::to_entity_id(
            void) const {

            const u32 hash = hash_string(
                (char*)&this->val[0], // cstr
                ENTITY_TAG_SIZE       // length
            );

            entity_id id(hash);
            return(id);
        }
    };

    struct entity {
        entity_tag* tag;
        entity_id   id;
    };
};

#endif IFB_ENGINE_ENTITY_HPP