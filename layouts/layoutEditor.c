#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

Clay_RenderCommandArray layoutEditor() {
    Clay_BeginLayout(); // BEGIN LAYOUT

    // layout tools
    Clay_Sizing toolLayoutExpand = {
        .width = CLAY_SIZING_GROW(0),
        .height = CLAY_SIZING_GROW(0)
    };

    // layout
    CLAY(CLAY_ID("layoutEditor_background"), {
        .backgroundColor = COLOUR_BACKGROUND,
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = toolLayoutExpand
        }
    }) {
        layoutMenuBar();
    }

    // END LAYOUT
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}