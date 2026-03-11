#ifndef LAYOUTS_H
#define LAYOUTS_H

#include "../includes/clay.h"

// main layout
Clay_RenderCommandArray layoutEditor();

// sub layouts
void layoutMenuBar();
void layoutTimeline();
void layoutMidiEditor();
void layoutPlugins(float widthPercent);
void layoutTrack(AudioTrack *track);
void layoutClip(AudioClip *clip);

#endif