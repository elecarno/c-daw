#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// layout function
void layoutMidiEditor() {
    CLAY(CLAY_ID("layoutMidiEditor"), {
        .layout = {
            .sizing = { 
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            },
            .childGap = 8
        },
        .backgroundColor = COLOUR_BUTTON_MAIN
    }) {
    
    }
}