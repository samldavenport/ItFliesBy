#ifndef IFB_ENGINE_GUI_UTILS_HPP
#define IFB_ENGINE_GUI_UTILS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-string.hpp"

namespace ifb::eng {


    using gui_text_size_t = dims_u32_size_t;

    IFB_ENG_INTERNAL_INLINE u32             gui_util_get_unique_id          (void);
    IFB_ENG_INTERNAL_INLINE gui_text_size_t gui_util_get_text_size          (const u32 text_length = 0);
    IFB_ENG_INTERNAL_INLINE string_c32_t    gui_util_get_string_c32_named   (const cchar* label);
    IFB_ENG_INTERNAL_INLINE string_c32_t    gui_util_get_string_c32_unnamed (const cchar* label);

    IFB_ENG_INTERNAL_INLINE u32
    gui_util_get_unique_id(
        void) {

        static u32 id = 0xFFFFFFFF;
        ++id;
        return(id);
    }
    
    IFB_ENG_INTERNAL_INLINE gui_text_size_t 
    gui_widget_get_text_size(
        const u32 text_length) {

        gui_text_size_t  size;
        size.width  = ImGui::CalcTextSize("A").x * text_length;
        size.height = ImGui::GetTextLineHeightWithSpacing();
        return(size);
    }

    IFB_ENG_INTERNAL_INLINE string_c32_t
    gui_util_get_string_c32_named(
        const cchar* label) {

        const u32 id = gui_util_get_unique_id();

        string_c32_t string;

        // name##name-id
        sprintf(
            string.chars,
            "%s##%s-%d",
            label, label, id
        );

        return(string);
    }

    IFB_ENG_INTERNAL_INLINE string_c32_t
    gui_util_get_string_c32_unnamed(
        const cchar* label) {

        const u32 id = gui_util_get_unique_id();

        string_c32_t string;

        // ##name-id
        sprintf_s(
            string.chars,
            STRING_SIZE_C32,
            "##%s-%d",
            label, id
        );

        return(string);
    }

};
 
#endif //IFB_ENGINE_GUI_UTILS_HPP
