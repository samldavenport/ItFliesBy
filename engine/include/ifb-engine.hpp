#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>
#include "ifb-engine-config.hpp"

#define IFB_ENG_API             __declspec(dllexport)
#define IFB_ENG_API_INLINE      inline
#define IFB_ENG_INLINE          inline
#define IFB_ENG_GLOBAL          static
#define IFB_ENG_LOCAL           static
#define IFB_ENG_INTERNAL        static
#define IFB_ENG_INTERNAL_INLINE static inline

using namespace sld;

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct error  : s32_t { };
    struct handle : u32_t { };
    struct flags  : u32_t { };
    struct context;
    struct color_u32;
    struct color_4xf32;
    struct tag;
    struct vec2;
    struct vec3;
    struct position;
    struct rotation;
    struct translation;
    struct scale;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr byte COLOR_BYTE_MAX      = 255;
    constexpr f32  COLOR_NORMAL_FACTOR = (1.0f / 255.0f);

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------
    
    IFB_ENG_API context* context_create      (byte* stack_data, const u64 stack_size);
    IFB_ENG_API bool     context_startup     (context* ctx);
    IFB_ENG_API bool     context_shutdown    (context* ctx);
    IFB_ENG_API bool     context_update      (context* ctx);
    IFB_ENG_API bool     context_render      (context* ctx);
    IFB_ENG_API bool     context_should_quit (context* ctx);

    //-------------------------------------------------------------------
    // COLOR
    //-------------------------------------------------------------------

    struct color_u32 {
        union {
            struct {
                byte r;
                byte g;
                byte b;
                byte a;
            };
            u32 hex;
        };

        IFB_ENG_API_INLINE void to_4xf32(color_4xf32& color) const;
    };

    struct color_4xf32 {
        f32 r;
        f32 g;
        f32 b;
        f32 a;

        IFB_ENG_API_INLINE void to_u32    (color_u32& color) const;
        IFB_ENG_API_INLINE void from_u32  (const color_u32& color);
        IFB_ENG_API_INLINE void from_rgba (const byte r, const byte g, const byte b, const byte a);
    };

    IFB_ENG_API_INLINE void
    color_u32::to_4xf32(
        color_4xf32& color) const {
        
        color.r = ((f32)this->r * COLOR_NORMAL_FACTOR);
        color.g = ((f32)this->g * COLOR_NORMAL_FACTOR);
        color.b = ((f32)this->b * COLOR_NORMAL_FACTOR);
        color.a = ((f32)this->a * COLOR_NORMAL_FACTOR);
    }

    IFB_ENG_API_INLINE void
    color_4xf32::to_u32(
        color_u32& color) const {

        color.r = ((byte)this->r * COLOR_BYTE_MAX);
        color.g = ((byte)this->g * COLOR_BYTE_MAX);
        color.b = ((byte)this->b * COLOR_BYTE_MAX);
        color.a = ((byte)this->a * COLOR_BYTE_MAX);            
    }

    IFB_ENG_API_INLINE void
    color_4xf32::from_u32(
        const color_u32& color) {

        this->r = (color.r * COLOR_BYTE_MAX);
        this->g = (color.g * COLOR_BYTE_MAX);
        this->b = (color.b * COLOR_BYTE_MAX);
        this->a = (color.a * COLOR_BYTE_MAX);
    }

    IFB_ENG_API_INLINE void
    color_4xf32::from_rgba(
        const byte r,
        const byte g,
        const byte b,
        const byte a) {

        this->r = (r * COLOR_NORMAL_FACTOR);
        this->g = (g * COLOR_NORMAL_FACTOR);
        this->b = (b * COLOR_NORMAL_FACTOR);
        this->a = (a * COLOR_NORMAL_FACTOR);
    }

    //-------------------------------------------------------------------
    // MATH
    //-------------------------------------------------------------------

    struct vec2 {
        union {
            struct {
                f32 x;
                f32 y;
            };
            f32 buffer[2];
        };
    };

    struct vec3 {
        union {
            struct {
                f32 x;
                f32 y;
                f32 z;
            };
            f32 buffer[3];
        };
    };

    //-------------------------------------------------------------------
    // TRANSFORMS
    //-------------------------------------------------------------------

    struct position    : vec3 { };
    struct rotation    : vec3 { };
    struct translation : vec3 { };
    struct scale       : vec3 { };
};

#endif //IFB_ENGINE_HPP