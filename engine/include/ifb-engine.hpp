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


namespace ifb {

    //-------------------------------------------------------------------
    // PRIMITIVES
    //-------------------------------------------------------------------

    // signed integers
    typedef sld::s8  s8;
    typedef sld::s16 s16;
    typedef sld::s32 s32;
    typedef sld::s64 s64;

    // unsigned integers
    typedef sld::u8  u8;
    typedef sld::u16 u16;
    typedef sld::u32 u32;
    typedef sld::u64 u64;
    
    // floats
    typedef sld::f32 f32;
    typedef sld::f64 f64;
    
    // booleans
    typedef sld::b8  b8;
    typedef sld::b16 b16;
    typedef sld::b32 b32;
    typedef sld::b64 b64;

    // chars  
    typedef sld::c8  cchar;
    typedef sld::c16 wchar;

    // memory
    typedef sld::byte  byte;
    typedef sld::addr  addr;
    typedef sld::vptr  vptr;
    typedef sld::pad8  pad8;
    typedef sld::pad16 pad16;
    typedef sld::pad32 pad32;
    typedef sld::pad64 pad64;

    // structured
    typedef sld::s8_t   s8_t;
    typedef sld::s16_t  s16_t;
    typedef sld::s32_t  s32_t;
    typedef sld::s64_t  s64_t;
    typedef sld::u8_t   u8_t;
    typedef sld::u16_t  u16_t;
    typedef sld::u32_t  u32_t;
    typedef sld::u64_t  u64_t;
    typedef sld::f32_t  f32_t;
    typedef sld::f64_t  f64_t;
    typedef sld::b8_t   b8_t;
    typedef sld::b16_t  b16_t;
    typedef sld::b32_t  b32_t;
    typedef sld::b64_t  b64_t;
    typedef sld::c8_t   c8_t;
    typedef sld::c16_t  c16_t;
    typedef sld::c32_t  c32_t;
    typedef sld::byte_t byte_t;
    typedef sld::addr_t addr_t;
    typedef sld::vptr_t vptr_t;

    // handles
    struct h8_t  : u8_t  { };
    struct h16_t : u16_t { };
    struct h32_t : u32_t { };
    struct h64_t : u64_t { };

    //-------------------------------------------------------------------
    // ERROR
    //-------------------------------------------------------------------

    struct eng_error_s32_t : s32_t { };

    enum eng_error_e32_type_ {
        eng_error_e32_type_success = 0x10000000,
        eng_error_e32_type_warning = 0x00000000,
        eng_error_e32_type_failure = 0x80000000,
    };

    enum eng_error_e32_module_ {
        eng_error_e32_module_platform = 0x00000000, 
        eng_error_e32_module_core     = 0x00010000, 
        eng_error_e32_module_memory   = 0x00020000, 
        eng_error_e32_module_file     = 0x00030000,
        eng_error_e32_module_asset    = 0x00040000
    };

    //-------------------------------------------------------------------
    // STRINGS
    //-------------------------------------------------------------------
    
    typedef sld::cstr_t cstr_t;
    typedef sld::wstr_t wstr_t;

    //-------------------------------------------------------------------
    // DATA STRUCTURES
    //-------------------------------------------------------------------g
    
    typedef sld::buffer_t buffer_t;

    //-------------------------------------------------------------------
    // GEOMETRY
    //-------------------------------------------------------------------

    typedef sld::dims_u32_t      dims_u32_t;
    typedef sld::dims_u32_size_t dims_u32_size_t;
    typedef sld::dims_u32_pos_t  dims_u32_pos_t;

    typedef sld::dims_f32_t      dims_f32_t;
    typedef sld::dims_f32_size_t dims_f32_size_t;
    typedef sld::dims_f32_pos_t  dims_f32_pos_t;

    //-------------------------------------------------------------------
    // DATA FORMATS
    //-------------------------------------------------------------------

    using xml_doc_t    = sld::xml_doc_t;
    using xml_node_t   = sld::xml_node_t;
    using xml_attrib_t = sld::xml_attrib_t;
};

#endif //IFB_ENGINE_HPP