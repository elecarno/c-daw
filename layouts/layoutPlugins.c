#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// layout function
void layoutPlugins(float widthPercent) {
    CLAY(CLAY_ID("layoutPlugins"), {
        .layout = {
            .sizing = { 
                .width = CLAY_SIZING_PERCENT(widthPercent),
                .height = CLAY_SIZING_GROW()
            },
            .childGap = 8
        },
        .backgroundColor = COLOUR_BUTTON_MAIN
    }) {
    
    }
}