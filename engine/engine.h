#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include "../includes/miniaudio.h"

// define engine structure
typedef struct {
    float* pSampleData;
    ma_uint32 total_frames;   
    float volume;            // 0.0 to 1.0 (or higher for gain)
    ma_uint32 track_offset;
    bool is_muted;
    char name[64];
} AudioTrack;

typedef struct {
    AudioTrack tracks[4];   // 4 tracks for testing
    int track_count;
    ma_uint32 playhead; // the timeline cursor
    bool is_playing;
} DAWEngine;

#define DAW_FORMAT ma_format_f32
#define DAW_CHANNELS 2
#define DAW_SAMPLE_RATE 44100

extern DAWEngine g_Engine;

// functions from engine.c
bool AddTrackFromFile(DAWEngine* engine, const char* filePath);

#endif