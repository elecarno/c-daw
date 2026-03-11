#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// layout function
void layoutTimeline() {
    CLAY(CLAY_ID("layoutTimeline"), {
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = { 
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            },
            .childGap = 2
        },
        .backgroundColor = COLOUR_BUTTON_MAIN
    }) {
        for (int i = 0; i < g_Engine.track_count; i++){
            layoutTrack(&g_Engine.tracks[i]);
        }
    }
}