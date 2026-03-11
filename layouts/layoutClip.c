#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// layout function
void layoutClip(AudioClip *clip) {
    CLAY_AUTO_ID({
        .layout = {
            .sizing = { 
                .width = CLAY_SIZING_FIT(),
                .height = CLAY_SIZING_GROW()
            },
        },
        .backgroundColor = COLOUR_TRACK_GREEN
    }) {
    
    }
}