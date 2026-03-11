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
            .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_FIT(),
            }
        }
    }) {
        CLAY(CLAY_ID("layoutMenuOptions"), {
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIXED(320),
                    .height = CLAY_SIZING_GROW()
                },
                .childGap = 1
            }
        }) {
            cDropdown(CLAY_STRING("File"), dropdownItemsFile, 4, 1);
            cDropdown(CLAY_STRING("Edit"), dropdownItemsEdit, 2, 2);
            cDropdown(CLAY_STRING("View"), dropdownItemsView, 1, 3);
        }
    }
}