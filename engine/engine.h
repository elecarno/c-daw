#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include "../includes/miniaudio.h"

// define engine structure
typedef struct {
    float* pSampleData;
    ma_uint32 total_frames;
    ma_uint32 timeline_start; // position on the DAW timeline (in frames)
    char name[64];
} AudioClip;

typedef struct {
    AudioClip clips[8]; // max 8 clips for testing
    int clip_count;
    float volume;
    bool is_muted;
    char name[64];
} AudioTrack;

typedef struct {
    AudioTrack tracks[16];   // 16 tracks for testing
    int track_count;
    ma_uint32 playhead; // the timeline cursor
    bool is_playing;
} DAWEngine;

#define DAW_FORMAT ma_format_f32
#define DAW_CHANNELS 2
#define DAW_SAMPLE_RATE 44100

extern DAWEngine g_Engine;

// functions from engine.c
bool engineInitialise();
void enginePlay();
void engineStop();
void OpenFileDialogAudio();

#endif