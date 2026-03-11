#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// layout function
void layoutTrack(AudioTrack *track) {
    CLAY_AUTO_ID({ // TRACK CONTAINER
        .layout = {
            .sizing = { 
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIXED(100)
            },
            .childGap = 8,
            .childAlignment = {
                .x = CLAY_ALIGN_X_RIGHT
            }
        },
        .backgroundColor = COLOUR_PANEL
    }) {
        CLAY_AUTO_ID({ // TRACK HEADER
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIXED(110),
                    .height = CLAY_SIZING_GROW()
                },
                .padding = { 4, 4, 4, 4 }
            },
            .backgroundColor = COLOUR_TRACK_GREEN
        }) {
            CLAY_TEXT(utilFixedClayString(track->name), CLAY_TEXT_CONFIG({
                .fontId = FONT_ID_BODY_16,
                .fontSize = 16,
                .textColor = COLOUR_WHITE
            }));
        }
    }
}