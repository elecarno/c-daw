#include "includes/clay.h"
#include "globals.h"
#include <string.h>

// utilities
Clay_String utilFixedClayString(char *text) {
    return (Clay_String) {
        .length = (int)strlen(text),
        .chars = text
    };
}

// state
int activeDropdownId = -1;

// fonts
const int FONT_ID_BODY_16 = 0;

// colours
Clay_Color COLOUR_WHITE          = { 245, 245, 245, 255 };
Clay_Color COLOUR_BACKGROUND     = { 36, 36, 36, 255 };
Clay_Color COLOUR_BUTTON_MAIN    = { 54, 54, 54, 255 };
Clay_Color COLOUR_BUTTON_HOVER   = { 74, 74, 74, 255 };
Clay_Color COLOUR_PANEL          = { 65, 65, 65, 255 };

Clay_Color COLOUR_TRACK_GREEN    = { 79, 168, 103, 255 };