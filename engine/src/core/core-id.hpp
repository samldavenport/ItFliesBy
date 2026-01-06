#ifndef CORE_ID_HPP
#define CORE_ID_HPP

#include "ifb-engine.hpp"

namespace ifb::eng {

    struct id {
        u32 val;

        constexpr explicit id (const u32 v) : val(v) { }
        constexpr          id (void)        : val(0) { }

        inline bool operator== (const id& other)   { return(this->val == other.val); }
        friend bool operator== (id a, id b) { return(a.val == b.val);         }

        constexpr id&
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

#endif //CORE_ID_HPP