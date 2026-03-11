#include "../includes/clay.h"
#include "../includes/raylib.h"
#include "../headers/globals.h"
#include "../headers/components.h"

// Button interaction callback
void HandleButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, void* userData) {
    // cast void* back to the function pointer
    ButtonCallback onClick = (ButtonCallback)userData;
    
    // check for mouse click
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        if (onClick != NULL) {
            onClick();
        }

        // close any dropdowns (for if button is in a dropdown)
        activeDropdownId = -1;
    }
}

// Base Button
void cButton(Clay_String text, ButtonCallback onClick) {
    CLAY_AUTO_ID({
        .layout = {
            .padding = { 8, 8, 4, 4 },
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIT()
            }
        },
        .backgroundColor = Clay_Hovered() ? COLOUR_BUTTON_HOVER : COLOUR_BUTTON_MAIN
    }) {
        if (Clay_Hovered()) { SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); }

        Clay_OnHover(HandleButtonInteraction, (void*)onClick);

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FONT_ID_BODY_16,
            .fontSize = 16,
            .textColor = COLOUR_WHITE
        }));
    }
}
