#include "../includes/clay.h"
#include "../headers/globals.h"
#include "../headers/components.h"

bool dropdownVisible = false;

void HandleDropdownInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, void* userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        dropdownVisible = true;
    }
}

void cDropdown(Clay_String text, DropdownItem dropdownItems[], int itemCount) {
    Clay_ElementId buttonId = CLAY_IDI("cDropdownButton", text.length);
    Clay_ElementId dropdownMenuId = CLAY_IDI("cDropdownMenu", text.length);

    CLAY(CLAY_IDI("cDropdownContainer", text.length), {
        .layout = {
            .sizing = { .width = CLAY_SIZING_FIT() }
        }
    }) {
        CLAY(buttonId, {
            .layout = { .padding = { 16, 16, 8, 8 }},
            .backgroundColor = COLOUR_BUTTON_MAIN,
        }) {
            Clay_OnHover(HandleDropdownInteraction, NULL); // broken line

            CLAY_TEXT(text, CLAY_TEXT_CONFIG({
                .fontId = FONT_ID_BODY_16,
                .fontSize = 16,
                .textColor = COLOUR_WHITE
            }));
        }

        if (dropdownVisible) {
            CLAY(dropdownMenuId, {
                .backgroundColor = COLOUR_BUTTON_MAIN,
                .floating = {
                    .attachTo = CLAY_ATTACH_TO_PARENT,
                    .attachPoints = {
                        .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM,
                    },
                },
                .layout = {
                    .padding = {0, 0, 8, 8 },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM
                }
            }) {
                if (!Clay_PointerOver(buttonId) && !Clay_PointerOver(dropdownMenuId)) {
                    dropdownVisible = false;
                }

                for (int i = 0; i < itemCount; i++) {
                    DropdownItem item = dropdownItems[i];
                    
                    cButton(item.text, item.callback);
                    // if () {
                    //     dropdownVisible = false; 
                    // }
                }
            }
        }
    }
}
