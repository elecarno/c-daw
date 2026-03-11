#ifndef GLOBALS_H
#define GLOBALS_H

#include "../includes/clay.h"

// utilities
Clay_String utilFixedClayString(char *text);

// state
extern int activeDropdownId;

// fonts
extern const int FONT_ID_BODY_16;

// colours
extern Clay_Color COLOUR_WHITE;
extern Clay_Color COLOUR_BACKGROUND;
extern Clay_Color COLOUR_BUTTON_MAIN;
extern Clay_Color COLOUR_BUTTON_HOVER;
extern Clay_Color COLOUR_PANEL;

extern Clay_Color COLOUR_TRACK_GREEN;

#endif