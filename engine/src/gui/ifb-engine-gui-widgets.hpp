#ifndef IFB_ENGINE_GUI_WIDGETS_HPP
#define IFB_ENGINE_GUI_WIDGETS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-string.hpp"
#include "ifb-engine-gui-utils.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_widget_text_c32_t;
    struct gui_widget_text_c64_t;
    struct gui_widget_text_c256_t;
    struct gui_widget_button_t;
    struct gui_widget_input_t;
    struct gui_widget_input_text_t;

    IFB_ENG_INTERNAL_INLINE gui_widget_text_c32_t   gui_widget_text_c32_init     (const cchar* buffer);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_c32_t   gui_widget_text_c32_render   (const cchar* buffer);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_c64_t   gui_widget_text_c64_init     (const cchar* buffer);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_c64_t   gui_widget_text_c64_render   (const cchar* buffer);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_c256_t  gui_widget_text_c256_init    (const cchar* buffer);
    IFB_ENG_INTERNAL_INLINE gui_widget_text_c256_t  gui_widget_text_c256_render  (const cchar* buffer);

    IFB_ENG_INTERNAL_INLINE gui_widget_button_t     gui_widget_button_init       (const cchar* label);
    IFB_ENG_INTERNAL_INLINE bool                    gui_widget_button_render     (gui_widget_button_t& button);

    IFB_ENG_INTERNAL_INLINE gui_widget_input_text_t gui_widget_input_text_init   (const cchar* initial_value = NULL);
    IFB_ENG_INTERNAL_INLINE void                    gui_widget_input_text_render (gui_widget_input_text_t& input_text);
    IFB_ENG_INTERNAL_INLINE void                    gui_widget_input_text_clear  (gui_widget_input_text_t& input_text);

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gui_widget_text_c32_t {
        u32          length;
        string_c32_t string;
    };
    struct gui_widget_text_c64_t {
        u32          length;
        string_c64_t string;
    };
    struct gui_widget_text_c256_t {
        u32           length;
        string_c256_t string;
    };
    struct gui_widget_button_t {
        string_c32_t label;
    };
    struct gui_widget_input_text_t {
        string_c32_t  name;
        string_c256_t buffer;
    };

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_WIDGET_CSTR_UNNAMED[]  = "###";
    constexpr u32   GUI_WIDGET_SIZE_LABEL      = sizeof(string_c32_t); 
    constexpr u32   GUI_WIDGET_SIZE_NAME       = sizeof(string_c32_t); 
    constexpr u32   GUI_WIDGET_SIZE_INPUT      = sizeof(string_c256_t);
    constexpr u32   GUI_WIDGET_TEXT_LENGTH_MAX = 256;

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE gui_widget_text_c32_t
    gui_widget_text_c32_init(
        const cchar* buffer) {

        gui_widget_text_c32_t text;
        text.length = strnlen_s(buffer, STRING_SIZE_C32);
        strncpy_s(text.string.chars, buffer, text.length);

        return(text);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_text_c32_render(
        const gui_widget_text_c32_t& text) {

        const cchar* start = text.string.chars;
        const cchar* end   = start + text.length;
        ImGui::TextUnformatted(start, end); 
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_text_c64_t
    gui_widget_text_c64_init(
        const cchar* buffer) {

        gui_widget_text_c64_t text;
        text.length = strnlen_s(buffer, STRING_SIZE_C64);
        strncpy_s(text.string.chars, buffer, text.length);
        return(text);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_text_c64_render(
        const gui_widget_text_c64_t& text) {

        const cchar* start = text.string.chars;
        const cchar* end   = start + text.length;
        ImGui::TextUnformatted(start, end); 
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_text_c256_t
    gui_widget_text_c256_init(
        const cchar* buffer) {

        gui_widget_text_c256_t text;
        text.length = strnlen_s(buffer, STRING_SIZE_C256);
        strncpy_s(text.string.chars, buffer, text.length);
        return(text);        
    }
    IFB_ENG_INTERNAL_INLINE void
    gui_widget_text_c256_render(
        const gui_widget_text_c256_t& text) {

        const cchar* start = text.string.chars;
        const cchar* end   = start + text.length;
        ImGui::TextUnformatted(start, end); 
    }

    
    IFB_ENG_INTERNAL_INLINE gui_widget_button_t
    gui_widget_button_init(
        const cchar* label) {

        gui_widget_button_t button;
        button.label = gui_util_get_string_c32_named(label); 
        return(button);
    }

    IFB_ENG_INTERNAL_INLINE bool
    gui_widget_button_render(
        gui_widget_button_t& button) {

        if (ImGui::Button(button.label.chars)) {
            return(true);
        }
        return(false);
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_input_text_t
    gui_widget_input_text_init(
        const cchar* initial_value) {

        gui_widget_input_text_t input_text;
        input_text.name = gui_util_get_string_c32_unnamed("text-input");

        if (initial_value != NULL) sprintf_s (input_text.buffer.chars, GUI_WIDGET_SIZE_INPUT, "%s", initial_value);
        else                       memset    (input_text.buffer.chars, 0, GUI_WIDGET_SIZE_INPUT); 
        return(input_text);        
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_input_text_render(
        gui_widget_input_text_t& input_text) {

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); // Set width to available content region
        ImGui::InputText(
            input_text.name.chars,
            input_text.buffer.chars,
            GUI_WIDGET_SIZE_INPUT
         );
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_input_text_clear(
        gui_widget_input_text_t& input_text) {
        
        memset(input_text.buffer.chars, 0, GUI_WIDGET_SIZE_INPUT); 
    }
};

#endif //IFB_ENGINE_GUI_WIDGETS_HPP