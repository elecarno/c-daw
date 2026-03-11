#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// interaction functions
void buttonImportFile() {
    OpenFileDialogAudio();
}

// layout function
void layoutMenuBar() {
    CLAY(CLAY_ID("layoutMenuBar"), {
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIXED(80)
            }
        }
    }) {
        cButton(CLAY_STRING("Import Audio File"), buttonImportFile);
    }
}