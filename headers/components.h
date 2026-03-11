#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../includes/clay.h"

// custom callback pointer for reuseable button components
typedef void (*ButtonCallback)(void);
typedef struct {
    Clay_String text;
    ButtonCallback callback;
} DropdownItem;


// components
void cButton(Clay_String text, ButtonCallback onClick);
void cDropdown(Clay_String text, DropdownItem dropdownItems[], int itemCount);

#endif