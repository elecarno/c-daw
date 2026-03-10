#include <stdio.h>
#include <stdbool.h>
#include <nfd.h>
#include "engine.h"

#define MINIAUDIO_IMPLEMENTATION
#include "../includes/miniaudio.h"


DAWEngine g_Engine = {0};

// CALLBACK ----------------------------------------------------------------------------------------
void mixing_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    DAWEngine* engine = (DAWEngine*)pDevice->pUserData; // Retrieve the engine
    if (!g_Engine.is_playing) return;

    float* pOut = (float*)pOutput;
    // clear the output buffer before playing any audio
    memset(pOut, 0, frameCount * pDevice->playback.channels * sizeof(float));

    for (int t = 0; t < g_Engine.is_playing; t++) {
        AudioTrack* track = &g_Engine.tracks[t];
        if (track->is_muted) continue;

        for (ma_uint32 i = 0; i < frameCount; i++) {
            ma_uint32 globalFrame = g_Engine.playhead + i;

            // Check if the global cursor is within this track's range
            if (globalFrame >= track->track_offset && 
                globalFrame < track->track_offset + track->total_frames) {
                
                ma_uint32 localFrame = globalFrame - track->track_offset;
                
                // Mix Left Channel
                pOut[i * 2] += track->pSampleData[localFrame * 2] * track->volume;
                // Mix Right Channel
                pOut[i * 2 + 1] += track->pSampleData[localFrame * 2 + 1] * track->volume;
            }
        }
    }

    g_Engine.playhead += frameCount;
}


// DECODER -----------------------------------------------------------------------------------------
bool AddTrackFromFile(DAWEngine* engine, const char* filePath) {
    if (engine->track_count >= 16) return false; // Simple limit for now

    ma_decoder decoder;
    // We tell miniaudio: "Whatever the file is, give it to me in f32, Stereo, 44.1kHz"
    ma_decoder_config config = ma_decoder_config_init(DAW_FORMAT, DAW_CHANNELS, DAW_SAMPLE_RATE);
    
    if (ma_decoder_init_file(filePath, &config, &decoder) != MA_SUCCESS) {
        return false;
    }

    ma_uint64 frameCount;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);

    // Allocate the buffer for this specific track
    float* pBuffer = (float*)malloc(frameCount * DAW_CHANNELS * sizeof(float));
    
    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(&decoder, pBuffer, frameCount, &framesRead);

    // Set up the new track in our engine
    AudioTrack* newTrack = &engine->tracks[engine->track_count];
    newTrack->pSampleData = pBuffer;
    newTrack->total_frames = (ma_uint32)framesRead;
    newTrack->volume = 0.8f; // Default volume
    newTrack->track_offset = 0; // Starts at the beginning of the timeline
    newTrack->is_muted = false;
    snprintf(newTrack->name, 64, "Track %d", engine->track_count + 1);

    engine->track_count++;

    ma_decoder_uninit(&decoder);
    return true;
}

// FILE LOADING ------------------------------------------------------------------------------------
void HandleLoadButton() {
    nfdchar_t *outPath = NULL;
    // Filter for audio files
    nfdfilteritem_t filterItem[3] = { { "Audio Files", "wav,mp3,flac" }, { "WAV", "wav" }, { "MP3", "mp3" } };
    
    // This opens the actual Windows/Mac/Linux file picker
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 3, NULL);

    if (result == NFD_OKAY) {
        printf("Success! Loading: %s\n", outPath);
        
        // Use the function we wrote earlier!
        AddTrackFromFile(&g_Engine, outPath);
        
        // Remember to free the path memory allocated by NFD
        NFD_FreePath(outPath);
    } 
    else if (result == NFD_CANCEL) {
        printf("User pressed cancel.\n");
    } 
    else {
        printf("Error: %s\n", NFD_GetError());
    }
}