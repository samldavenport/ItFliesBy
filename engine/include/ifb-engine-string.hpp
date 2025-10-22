#ifndef IFB_ENGINE_STRING_HPP
#define IFB_ENGINE_STRING_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb::eng {

    struct string_c32_t  { cchar chars[32];  };
    struct string_c64_t  { cchar chars[64];  };
    struct string_c256_t { cchar chars[256]; };

    constexpr u32 STRING_SIZE_C32  = sizeof(string_c32_t); 
    constexpr u32 STRING_SIZE_C64  = sizeof(string_c64_t); 
    constexpr u32 STRING_SIZE_C256 = sizeof(string_c256_t); 

    IFB_ENG_API_INLINE void          cstr_sanitize(const cchar* cstr, const u64 size);

    IFB_ENG_API_INLINE string_c32_t* string_c32_arena_alloc (eng_mem_arena_t*    arena, const u32 count = 1);
    IFB_ENG_API_INLINE cstr_t        string_c32_to_cstr     (const string_c32_t* string);
    IFB_ENG_API_INLINE void          string_c32_sanitize    (string_c32_t*       string);
    IFB_ENG_API_INLINE u64           string_c32_copy_from   (string_c32_t*       string, const cchar* src);
    IFB_ENG_API_INLINE u64           string_c32_copy_to     (const string_c32_t* string, cchar*       dst);
    
    IFB_ENG_API_INLINE cstr_t        string_c64_to_cstr    (string_c64_t* string);
    IFB_ENG_API_INLINE void          string_c64_sanitize   (string_c64_t* string);
    IFB_ENG_API_INLINE u64           string_c64_copy_from  (string_c64_t* string, const cchar* src);
    IFB_ENG_API_INLINE u64           string_c64_copy_to    (const string_c64_t* string, cchar* dst);
    
    IFB_ENG_API_INLINE cstr_t         string_c256_to_cstr   (string_c256_t* string);
    IFB_ENG_API_INLINE void          string_c256_sanitize  (string_c256_t* string);
    IFB_ENG_API_INLINE u64           string_c256_copy_from (string_c256_t* string, const cchar* src);
    IFB_ENG_API_INLINE u64           string_c256_copy_to   (const string_c256_t* string, cchar* dst);

    IFB_ENG_API_INLINE void
    cstr_sanitize(
        cchar*    cstr,
        const u64 size) {

        constexpr u32 ascii_lowercase_offset = 32; 

        bool is_terminated = false;

        for (
            u32 char_index = 0;
            char_index < size;
            ++char_index) {

            const cchar c = cstr[char_index];

            is_terminated |= (c == 0);
            if (is_terminated) {
                cstr[char_index] = 0;
                continue;                    
            }

            const bool is_lower_case   = (c >= 'a' && c <= 'z');
            const bool is_upper_case   = (c >= 'A' && c <= 'Z');
            const bool is_number       = (c >= '0' && c <= '9');
            const bool is_special_char = (!is_lower_case && !is_upper_case && !is_number);

            if      (is_terminated)   cstr[char_index] = 0;
            else if (is_upper_case)   cstr[char_index] = (c + ascii_lowercase_offset);
            else if (is_special_char) cstr[char_index] = '-';
        }
    }

    IFB_ENG_API_INLINE string_c32_t*
    string_c32_arena_alloc(
        eng_mem_arena_t* arena,
        const u32        count) {

        const u32     size   = (STRING_SIZE_C32 * count);
        string_c32_t* string = (string_c32_t*)sld::arena_push_bytes(arena, size);
        assert(string);

        sld::memory_zero_struct<string_c32_t>(string);

        return(string);
    }

    IFB_ENG_API_INLINE cstr_t
    string_c32_to_cstr(
        const string_c32_t* string) {

        assert(string);

        cstr_t cstr;
        cstr.chars = (cchar*)string->chars;
        cstr.size  = STRING_SIZE_C32;

        return(cstr);
    }


    IFB_ENG_API_INLINE void
    string_c32_sanitize(
        string_c32_t* string) {
        
        assert(string);
        cstr_sanitize(string->chars, STRING_SIZE_C32);
    }
    
    IFB_ENG_API_INLINE u64
    string_c32_copy_from(
        string_c32_t* string,
        const cchar*  src) {

        cstr_t    dst          = string_c32_to_cstr(string);
        const u64 bytes_copied = sld::cstr_copy_from(&dst, src, STRING_SIZE_C32);
        return(bytes_copied);
    }

    IFB_ENG_API_INLINE u64
    string_c32_copy_to(
        const string_c32_t* string,
        cchar*             dst) {

        cstr_t    src          = string_c32_to_cstr (string);
        const u64 bytes_copied = sld::cstr_copy_to  (&src, dst, STRING_SIZE_C32);
        return(bytes_copied);
    }

    IFB_ENG_API_INLINE void
    string_c64_sanitize(
        string_c64_t* string) {

        assert(string);
        cstr_sanitize(string->chars, sizeof(string_c64_t));
    }

    IFB_ENG_API_INLINE void
    string_c256_sanitize(
        string_c256_t* string) {
        
        assert(string);
        cstr_sanitize(string->chars, sizeof(string_c256_t));
    }
};

#endif //IFB_ENGINE_STRING_HPP