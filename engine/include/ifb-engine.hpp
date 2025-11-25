#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>

#define IFB_ENG_API             __declspec(dllexport)
#define IFB_ENG_API_INLINE      inline
#define IFB_ENG_INLINE          inline
#define IFB_ENG_GLOBAL          static
#define IFB_ENG_LOCAL           static
#define IFB_ENG_INTERNAL        static
#define IFB_ENG_INTERNAL_INLINE static inline

using namespace sld;

namespace ifb::eng {

    struct error  : s32_t { };
    struct handle : u32_t { };
    struct flags  : u32_t { };
    struct context;

    IFB_ENG_API context* context_create      (byte* stack_data, const u64 stack_size);
    IFB_ENG_API bool     context_startup     (context* ctx);
    IFB_ENG_API bool     context_shutdown    (context* ctx);
    IFB_ENG_API bool     context_update      (context* ctx);
    IFB_ENG_API bool     context_render      (context* ctx);
    IFB_ENG_API bool     context_should_quit (context* ctx);

};

#define IFB_ENG_CONFIG_OS_MAX_COUNT_MONITORS 16
#define IFB_ENG_CONFIG_OS_MAX_COUNT_FILES    64

#endif //IFB_ENGINE_HPP