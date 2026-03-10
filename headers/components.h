#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../includes/clay.h"

// custom callback pointer for reuseable button components
typedef void (*ButtonCallback)(void);

void cButton(Clay_String text, ButtonCallback onClick);

#endif