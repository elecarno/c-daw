#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../includes/clay.h"

typedef void (*ButtonAction)(void);

void cButton(Clay_String text, ButtonAction onClick);

#endif