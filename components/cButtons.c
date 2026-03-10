#include "../includes/clay.h"
#include "../headers/globals.h"
#include "../headers/components.h"

// Button interaction callback
void HandleButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, void* userData) {
    ButtonAction onClick = (ButtonAction)userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        if (onClick != NULL) {
            onClick();
        }
    }
}

// Base Button
void cButton(Clay_String text, ButtonAction onClick) {
    CLAY(
        CLAY_IDI("Button", text.length), {
        .layout = { .padding = { 16, 16, 8, 8 }},
        .backgroundColor = { 140, 140, 140, 255 },
        .cornerRadius = CLAY_CORNER_RADIUS(5)
    }) {
        Clay_OnHover(HandleButtonInteraction, (void*)onClick);

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FONT_ID_BODY_16,
            .fontSize = 16,
            .textColor = { 255, 255, 255, 255 }
        }));
    }
}
