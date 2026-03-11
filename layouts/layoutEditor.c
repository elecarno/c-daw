#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

Clay_RenderCommandArray layoutEditor() {
    Clay_BeginLayout(); // BEGIN LAYOUT
    
    // layout
    CLAY(CLAY_ID("layoutEditor"), {
        .backgroundColor = COLOUR_BACKGROUND,
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            },
            .childGap = 8
        }
    }) {
        layoutMenuBar();

        CLAY(CLAY_ID("layoutWorkspace"), {
            .layout = { 
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
                .sizing = {
                    .width = CLAY_SIZING_GROW(),
                    .height = CLAY_SIZING_GROW()
                },
                .childGap = 8
            }
        }) {
            CLAY(CLAY_ID("layoutTimelineWorkspace"), {
                .layout = { 
                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                    .sizing = {
                        .width = CLAY_SIZING_PERCENT(0.75),
                        .height = CLAY_SIZING_GROW()
                    } 
                }
            }) {
                layoutTimeline();

                layoutMidiEditor();
            }

            layoutPlugins(0.25);
        }
    }

    // END LAYOUT
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}