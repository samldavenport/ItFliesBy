#ifndef ENTITY_TAG_HPP
#define ENTITY_TAG_HPP

#include <stdio.h>

#include "ifb-engine.hpp"
#include "entity.hpp"


namespace ifb::eng {

    constexpr u32 ENTITY_TAG_SIZE = 32;    

    struct entity_tag {

        // members
        cchar val[ENTITY_TAG_SIZE];

        // methods
        inline entity_tag  (const cchar* cstr);
        inline entity_id to_id (void);

    };

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
        void) {

        const u32 hash = hash_string(
            (char*)&this->val[0], // cstr
            ENTITY_TAG_SIZE       // length
        );

        entity_id id(hash);
        return(id);
    }

};

#endif //ENTITY_TAG_HPP