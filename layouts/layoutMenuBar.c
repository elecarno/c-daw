#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// interaction functions
void buttonImportFile() {
    OpenFileDialogAudio();
}

// dropdown options = { "Import Audio", buttonImportFile };
DropdownItem dropdownItems[] = { 
    { CLAY_STRING("Import Audio"), buttonImportFile } 
};

// layout function
void layoutMenuBar() {
    CLAY(CLAY_ID("layoutMenuBar"), {
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIXED(30)
            }
        }
    }) {
        // cButton(CLAY_STRING("Import Audio File"), buttonImportFile);
        cDropdown(CLAY_STRING("File"), dropdownItems, 1);
    }
}