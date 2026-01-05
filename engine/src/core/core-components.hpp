#ifndef GRAPHICS_TYPES
#define GRAPHICS_TYPES

#include "ifb-engine.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct color_u32;
    struct color_4xf32;
    struct tag;
    struct vec2;
    struct vec3;
    struct position;
    struct rotation;
    struct translation;
    struct scale;
    struct quad;

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr byte COLOR_BYTE_MAX      = 255;
    constexpr f32  COLOR_NORMAL_FACTOR = (1.0f / 255.0f);
    constexpr f32  PI_32               = 3.1415927410125732421875f;
    constexpr f64  PI_64               = 3.14159265358979323846264338327950288;

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
};

#endif //GRAPHICS_TYPES