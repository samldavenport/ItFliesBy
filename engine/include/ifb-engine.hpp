#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>
#include <sld-hash.hpp>
#include <sld-cstr.hpp>
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

    struct error_t  : s32_t { };
    struct handle_t : u32_t { };
    struct flags_t  : u32_t { };
    struct context_t;

    IFB_ENG_API context_t* context_create      (byte* stack_data, const u64 stack_size);
    IFB_ENG_API bool       context_startup     (context_t* context);
    IFB_ENG_API bool       context_shutdown    (context_t* context);
    IFB_ENG_API bool       context_update      (context_t* context);
    IFB_ENG_API bool       context_render      (context_t* context);
    IFB_ENG_API bool       context_should_quit (context_t* context);

};

#endif //IFB_ENGINE_HPP