#ifndef CORE_ENTITY_HPP
#define CORE_ENTITY_HPP

#include <stdio.h>

#include "ifb-engine.hpp"
#include "core-hash.hpp"
#include "core-id.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    using entity_id = id;

    struct entity;
    struct entity_tag;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr u32 ENTITY_ID_INVALID = 0;
    constexpr u32 ENTITY_TAG_SIZE   = 32;    

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

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
        entity_tag::to_id(
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

#endif //CORE_ENTITY_HPP
