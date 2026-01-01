#ifndef ENTITY_ID_HPP
#define ENTITY_ID_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    struct entity_id {
        u32 val;

        constexpr explicit entity_id (const u32 v) : val(v) { }
        constexpr          entity_id (void)        : val(0) { }

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
};

#endif //ENTITY_ID_HPP