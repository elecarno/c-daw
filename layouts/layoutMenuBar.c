#include "../includes/clay.h"
#include "../engine/engine.h"
#include "../headers/globals.h"
#include "../headers/components.h"
#include "../headers/layouts.h" 

// interaction functions
void buttonOpenProject() {}

void buttonSaveProject() {}

void buttonImportAudio() {
    OpenFileDialogAudio();
}

void buttonExportAudio() {}

void buttonUndo() {}

void buttonRedo() {}

void nothing() {}

// dropdown options = { "Import Audio", buttonImportFile };
DropdownItem dropdownItemsFile[] = { 
    { CLAY_STRING("Open Project"), buttonOpenProject },
    { CLAY_STRING("Save Project"), buttonSaveProject },
    { CLAY_STRING("Import Audio"), buttonImportAudio },
    { CLAY_STRING("Export Audio"), buttonExportAudio }
};

DropdownItem dropdownItemsEdit[] = { 
    { CLAY_STRING("Undo"), buttonUndo },
    { CLAY_STRING("Redo"), buttonRedo }
};

DropdownItem dropdownItemsView[] = { 
    { CLAY_STRING("View Option"), nothing }
};

// layout function
void layoutMenuBar() {
    CLAY(CLAY_ID("layoutMenuBar"), {
        .layout = {
            .sizing = { .width = CLAY_SIZING_GROW() },
            .childGap = 8
        }
    }) {
        CLAY(CLAY_ID("layoutMenuOptions"), {
            .layout = { 
                .sizing = { .width = CLAY_SIZING_PERCENT(0.2) },
                .childGap = 2 
            }
        }) {
            cDropdown(CLAY_STRING("File"), dropdownItemsFile, 4, 1);
            cDropdown(CLAY_STRING("Edit"), dropdownItemsEdit, 2, 2);
            cDropdown(CLAY_STRING("View"), dropdownItemsView, 1, 3);
        }

        CLAY(CLAY_ID("layoutMenuRhythm"), {
            .layout = { 
                .sizing = { .width = CLAY_SIZING_PERCENT(0.2) },
                .childGap = 2 
            }
        }) {
            cButton(CLAY_STRING("120 BPM"), nothing);
            cButton(CLAY_STRING("4/4"), nothing);
        }

        CLAY(CLAY_ID("layoutMenuControl"), {
            .layout = { 
                .sizing = { .width = CLAY_SIZING_PERCENT(0.2) },
                .childGap = 2 
            }
        }) {
            cButton(CLAY_STRING("Play"), nothing);
            cButton(CLAY_STRING("Stop"), nothing);
            cButton(CLAY_STRING("Record"), nothing);
        }

        CLAY(CLAY_ID("layoutMenuTime"), {
            .layout = { 
                .sizing = { .width = CLAY_SIZING_PERCENT(0.2) },
                .childGap = 2 
            }
        }) {
            // time in bars (bar . crochet . quaver . semiquaver)
            cButton(CLAY_STRING("0 . 0 . 0 . 0"), nothing);
            // time in minutes:seconds
            cButton(CLAY_STRING("00 : 00"), nothing);
        }

        CLAY(CLAY_ID("layoutMenuDevice"), {
            .layout = { 
                .sizing = { .width = CLAY_SIZING_PERCENT(0.2) },
                .childGap = 2 
            },
        }) {
            cButton(CLAY_STRING("MIDI"), nothing);
            cButton(CLAY_STRING("CPU: 50\%"), nothing);
        }
    }
}