#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>
#include <sld-hash.hpp>
#include <sld-cstr.hpp>
#include <sld-wstr.hpp>
#include <sld-xml.hpp>
#include <sld-geometry.hpp>

#define IFB_ENG_API             __declspec(dllexport)
#define IFB_ENG_API_INLINE      inline
#define IFB_ENG_INLINE          inline
#define IFB_ENG_GLOBAL          static
#define IFB_ENG_LOCAL           static
#define IFB_ENG_INTERNAL        static
#define IFB_ENG_INTERNAL_INLINE static inline

using namespace sld;

namespace ifb::eng {

    struct u32_t {
        
        u32 val;
    
        constexpr bool operator == (const u32_t& other) const noexcept { return(this->val == other.val); }
        constexpr bool operator != (const u32_t& other) const noexcept { return(this->val != other.val); }
        constexpr bool operator <= (const u32_t& other) const noexcept { return(this->val <= other.val); }
        constexpr bool operator >= (const u32_t& other) const noexcept { return(this->val >= other.val); }
        constexpr bool operator <  (const u32_t& other) const noexcept { return(this->val <  other.val); }
        constexpr bool operator >  (const u32_t& other) const noexcept { return(this->val >  other.val); }

        constexpr u32_t&
        operator=(u32 h) noexcept {
            this->val = h;
            return(*this);
        }
    };

    struct s32_t {
        
        s32 val;
    
        constexpr bool operator == (const s32_t& other) const noexcept { return(this->val == other.val); }
        constexpr bool operator != (const s32_t& other) const noexcept { return(this->val != other.val); }
        constexpr bool operator <= (const s32_t& other) const noexcept { return(this->val <= other.val); }
        constexpr bool operator >= (const s32_t& other) const noexcept { return(this->val >= other.val); }
        constexpr bool operator <  (const s32_t& other) const noexcept { return(this->val <  other.val); }
        constexpr bool operator >  (const s32_t& other) const noexcept { return(this->val >  other.val); }

        constexpr s32_t&
        operator=(s32 h) noexcept {
            this->val = h;
            return(*this);
        }
    };

    //-------------------------------------------------------------------
    // HANDLE
    //-------------------------------------------------------------------

    constexpr u32 HANDLE_INVALID = 0xFFFFFFFF;

    struct handle_t : u32_t {

        constexpr                   handle_t (void)                { this->val = HANDLE_INVALID;          }
        constexpr explicit          handle_t (u32 h)               { this->val = h;                       }
        constexpr explicit operator bool     (void) const noexcept { return(this->val != HANDLE_INVALID); }
    };

    //-------------------------------------------------------------------
    // FLAGS
    //-------------------------------------------------------------------

    constexpr u32 FLAGS_NONE = 0;

    struct flags_t : u32_t {
        
        constexpr                   flags_t (void)                                { this->val = FLAGS_NONE;          }
        constexpr explicit          flags_t (u32 h)                               { this->val = h;                   }
        constexpr explicit operator bool    (void) const noexcept                 { return(this->val != FLAGS_NONE); }

        constexpr flags_t  operator ~       (void)                 const noexcept { return flags_t(~val);            }
        constexpr flags_t  operator |       (const flags_t& other) const noexcept { return flags_t(val | other.val); }
        constexpr flags_t  operator &       (const flags_t& other) const noexcept { return flags_t(val & other.val); }
        constexpr flags_t  operator ^       (const flags_t& other) const noexcept { return flags_t(val ^ other.val); }
        constexpr flags_t& operator |=      (const flags_t& other)       noexcept { val |= other.val; return *this;  }
        constexpr flags_t& operator &=      (const flags_t& other)       noexcept { val &= other.val; return *this;  }
        constexpr flags_t& operator ^=      (const flags_t& other)       noexcept { val ^= other.val; return *this;  }
        constexpr flags_t  operator |       (const u32 other)      const noexcept { return flags_t(val | other); }
        constexpr flags_t  operator &       (const u32 other)      const noexcept { return flags_t(val & other); }
        constexpr flags_t  operator ^       (const u32 other)      const noexcept { return flags_t(val ^ other); }
        constexpr flags_t& operator |=      (const u32 other)            noexcept { val |= other; return *this;  }
        constexpr flags_t& operator &=      (const u32 other)            noexcept { val &= other; return *this;  }
        constexpr flags_t& operator ^=      (const u32 other)            noexcept { val ^= other; return *this;  }
        constexpr flags_t  operator <<      (u32 bits)             const noexcept { return flags_t(val << bits);     }
        constexpr flags_t  operator >>      (u32 bits)             const noexcept { return flags_t(val >> bits);     }
        constexpr flags_t& operator <<=     (u32 bits)                   noexcept { val <<= bits; return *this;      }
        constexpr flags_t& operator >>=     (u32 bits)                   noexcept { val >>= bits; return *this;      }
    };

    //-------------------------------------------------------------------
    // ERROR
    //-------------------------------------------------------------------

    struct error_t : s32_t {
        constexpr                   error_t (void)                { this->val = 0;          }
        constexpr explicit          error_t (s32 e)               { this->val = e;          }
        constexpr explicit operator bool    (void) const noexcept { return(this->val >= 0); }
    };

    enum eng_error_e_type_ : u8 {
        eng_error_e_type_success = 0x10,
        eng_error_e_type_warning = 0x00,
        eng_error_e_type_failure = 0x80,
    };

    enum eng_error_e_module_ : u8 {
        eng_error_e_module_platform = 0x00, 
        eng_error_e_module_core     = 0x01, 
        eng_error_e_module_memory   = 0x02, 
        eng_error_e_module_file     = 0x03,
        eng_error_e_module_asset    = 0x04
    };
};

#endif //IFB_ENGINE_HPP