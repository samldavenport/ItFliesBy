#ifndef IFB_ENGINE_GUI_WIDGETS_HPP
#define IFB_ENGINE_GUI_WIDGETS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-string.hpp"
#include "ifb-engine-gui-utils.hpp"

namespace ifb::eng {

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    struct gui_widget_label_t;
    struct gui_widget_button_t;
    struct gui_widget_input_t;
    struct gui_widget_input_text_t;

    IFB_ENG_INTERNAL_INLINE gui_widget_label_t      gui_widget_label_init_unique (const cchar* label_text);
    IFB_ENG_INTERNAL_INLINE gui_widget_label_t      gui_widget_label_init        (const cchar* label_text);
    IFB_ENG_INTERNAL_INLINE void                    gui_widget_label_render      (gui_widget_label_t& label);

    IFB_ENG_INTERNAL_INLINE gui_widget_button_t     gui_widget_button_init       (const cchar* label);
    IFB_ENG_INTERNAL_INLINE bool                    gui_widget_button_render     (gui_widget_button_t& button);

    IFB_ENG_INTERNAL_INLINE gui_widget_input_text_t gui_widget_input_text_init   (const cchar* name);
    IFB_ENG_INTERNAL_INLINE void                    gui_widget_input_text_render (gui_widget_input_text_t& input_text);
    IFB_ENG_INTERNAL_INLINE void                    gui_widget_input_text_clear  (gui_widget_input_text_t& input_text);


    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct gui_widget_label_t {
        string_c32_t str_name;
    };

    struct gui_widget_button_t {
        string_c32_t str_label;
    };

    struct gui_widget_input_text_t {
        string_c32_t  str_name;
        string_c256_t str_text;
    };

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr cchar GUI_WIDGET_CSTR_UNNAMED[] = "###";
    constexpr u32   GUI_WIDGET_SIZE_LABEL     = sizeof(string_c32_t); 
    constexpr u32   GUI_WIDGET_SIZE_NAME      = sizeof(string_c32_t); 
    constexpr u32   GUI_WIDGET_SIZE_INPUT     = sizeof(string_c256_t);

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL_INLINE gui_widget_label_t
    gui_widget_label_init(
        const cchar* label_text) {

        gui_widget_label_t label;
        label.str_name = string_c32_static_init(label_text);
        return(label);
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_label_render(
        gui_widget_label_t& label) {

        ImGui::Text(label.str_name.chars);
    }
    
    IFB_ENG_INTERNAL_INLINE gui_widget_button_t
    gui_widget_button_init(
        const cchar* label) {

        gui_widget_button_t button;
        button.str_label = gui_util_get_string_c32_named(label); 
        return(button);
    }

    IFB_ENG_INTERNAL_INLINE bool
    gui_widget_button_render(
        gui_widget_button_t& button) {

        const bool button_clicked = ImGui::Button(button.str_label.chars);
        return(button_clicked);
    }

    IFB_ENG_INTERNAL_INLINE gui_widget_input_text_t
    gui_widget_input_text_init(
        const cchar* name) {

        assert(name != NULL);

        gui_widget_input_text_t input_text;
        input_text.str_name = gui_util_get_string_c32_unnamed(name);
        memset(input_text.str_text.chars, 0, GUI_WIDGET_SIZE_INPUT); 
        return(input_text);        
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_input_text_render(
        gui_widget_input_text_t& input_text) {

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x); // Set width to available content region
        ImGui::InputText(
            input_text.str_name.chars,
            input_text.str_text.chars,
            GUI_WIDGET_SIZE_INPUT
         );
    }

    IFB_ENG_INTERNAL_INLINE void
    gui_widget_input_text_clear(
        gui_widget_input_text_t& input_text) {
        
        memset(input_text.str_text.chars, 0, GUI_WIDGET_SIZE_INPUT); 
    }


};

#endif //IFB_ENGINE_GUI_WIDGETS_HPP