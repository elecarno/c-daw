#include "../includes/clay.h"
#include "../includes/raylib.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include <stdio.h>
#include <string.h>

void HandleDropdownInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, void* userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        int currentId = (int)(uintptr_t)userData;
        printf("%d", currentId);
        activeDropdownId = currentId;

        // if (activeDropdownId == currentId) {
        //     activeDropdownId = -1;
        // } else {
        //     activeDropdownId = currentId;
        // }
    }
}

void cDropdown(Clay_String text, DropdownItem dropdownItems[], int itemCount, int localId) {
    Clay_ElementId buttonId = CLAY_IDI("cDropdownButton", localId);
    Clay_ElementId dropdownMenuId = CLAY_IDI("cDropdownMenu", localId);

    CLAY(buttonId, {
        .layout = { 
            .padding = { 8, 8, 4, 4 },
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            }
        },
        .backgroundColor = Clay_Hovered() ? COLOUR_BUTTON_HOVER : COLOUR_BUTTON_MAIN
    }) {
        if (Clay_Hovered()) { SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); }

        Clay_OnHover(HandleDropdownInteraction, (void *)(uintptr_t)localId);

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FONT_ID_BODY_16,
            .fontSize = 16,
            .textColor = COLOUR_WHITE
        }));

        if (activeDropdownId == localId) {
            CLAY(dropdownMenuId, {
                .backgroundColor = COLOUR_BACKGROUND,
                .floating = {
                    .attachTo = CLAY_ATTACH_TO_PARENT,
                    .attachPoints = {
                        .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM
                    }
                },
                .layout = { 
                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                    .sizing = { .width = CLAY_SIZING_FIXED(160) },
                    .padding = { 1, 1, 1, 1},
                    .childGap = 1
                }
            }) {
                if (!Clay_PointerOver(buttonId) && !Clay_PointerOver(dropdownMenuId)) {
                    activeDropdownId = -1;
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
