#ifndef IFB_ENGINE_GUI_WIDGETS_HPP
#define IFB_ENGINE_GUI_WIDGETS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-string.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_WIDGET_CSTR_UNNAMED[] = "###";

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_widget_label_t;
    struct gui_widget_input_text_t;
    using  gui_widget_text_size_t = dims_u32_size_t;

    IFB_ENG_INTERNAL_INLINE u32                    gui_widget_get_unique_id       (void);
    IFB_ENG_INTERNAL_INLINE void                   gui_widget_render_static_label (const cchar* label_text);
    IFB_ENG_INTERNAL_INLINE gui_widget_label_t     gui_widget_get_unique_label    (const cchar* label_text);
    IFB_ENG_INTERNAL_INLINE gui_widget_label_t     gui_widget_get_label           (const cchar* label_text);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_size_t gui_widget_get_text_size       (const u32 text_length = 0);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gui_widget_label_t {
        string_c32_t string;
    };

    struct gui_widget_input_t {
        string_c256_t string;         
    };

    struct gui_widget_input_text_t {
        struct {
            gui_widget_label_t input;
            gui_widget_label_t button;
        } label;
        string_c256_t string;
    };

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE u32
    gui_widget_get_unique_id(
        void) {

        static u32 id = 0xFFFFFFFF;
        ++id;
        return(id);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_render_static_label(
        const cchar* label_text) {

        ImGui::Text(label_text);
    }


    IFB_ENG_INTERNAL_INLINE gui_widget_label_t
    gui_widget_get_unique_label(
        const cchar* label_text) {

        const u32 id = gui_widget_get_unique_id();

        gui_widget_label_t label;
        sprintf_s(label.string.chars, sizeof(label), "%s##%d",label_text, id);

        return(label);
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_label_t
    gui_widget_get_label(
        const cchar* label_text) {

        gui_widget_label_t label;
        sprintf_s(label.string.chars, sizeof(label), "%s",label_text);
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_text_size_t
    gui_widget_get_text_size(
        const u32 text_length) {

        gui_widget_text_size_t size;
        size.width  = ImGui::CalcTextSize("A").x * text_length;
        size.height = ImGui::GetTextLineHeightWithSpacing();
        return(size);
    }

};

#endif //IFB_ENGINE_GUI_WIDGETS_HPP