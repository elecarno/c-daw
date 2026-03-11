#include <stdio.h>
#include <stdbool.h>
#include <nfd.h>
#include "engine.h"

#define MINIAUDIO_IMPLEMENTATION
#include "../includes/miniaudio.h"


DAWEngine g_Engine = {0};
ma_device g_Device;

void mixing_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    DAWEngine* engine = (DAWEngine*)pDevice->pUserData;
    float* pOut = (float*)pOutput;

    // clear the buffer
    memset(pOut, 0, frameCount * DAW_CHANNELS * sizeof(float));

    // check if audio is being played
    if (!engine->is_playing) return;

    // loop through the loaded tracks
    for (int t = 0; t < engine->track_count; t++) {
        AudioTrack* track = &engine->tracks[t];
        
        if (track->is_muted || track->pSampleData == NULL) continue;

        for (ma_uint32 i = 0; i < frameCount; i++) {
            // calculate position on the global timeline
            ma_uint32 globalFrame = engine->playhead + i;

            // check if the track has audio at the calculated position
            if (globalFrame >= track->track_offset && 
                globalFrame < (track->track_offset + track->total_frames)) {
                
                ma_uint32 localFrame = globalFrame - track->track_offset;
                
                // mix the samples (additive mixing)
                // left channel
                pOut[i * 2] += track->pSampleData[localFrame * 2] * track->volume;
                // right channel
                pOut[i * 2 + 1] += track->pSampleData[localFrame * 2 + 1] * track->volume;
            }
        }
    }

    // advance the global playhead by the number of frames just processed
    engine->playhead += frameCount;
}

bool engineInitialise() {
    // device configuration
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = DAW_FORMAT;      // f32
    config.playback.channels = DAW_CHANNELS;    // 2
    config.sampleRate        = DAW_SAMPLE_RATE; // 44100
    config.dataCallback      = mixing_callback;
    config.pUserData         = &g_Engine;       // pass engine to the callback

    // initialize hardware device
    if (ma_device_init(NULL, &config, &g_Device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        return false;
    }

    // start audio thread
    if (ma_device_start(&g_Device) != MA_SUCCESS) {
        ma_device_uninit(&g_Device);
        return false;
    }

    return true;
}

void enginePlay() {
    g_Engine.is_playing = true;
    printf("Playback started at frame %u\n", g_Engine.playhead);
}

void engineStop() {
    g_Engine.is_playing = false;
    g_Engine.playhead = 0; 
    printf("Playback stopped.\n");
}

bool AddTrackFromFile(DAWEngine* engine, const char* filePath) {
    if (engine->track_count >= 16) return false; // Simple limit for now

    ma_decoder decoder;
    ma_decoder_config config = ma_decoder_config_init(DAW_FORMAT, DAW_CHANNELS, DAW_SAMPLE_RATE);
    
    if (ma_decoder_init_file(filePath, &config, &decoder) != MA_SUCCESS) {
        return false;
    }

    ma_uint64 frameCount;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);

    float* pBuffer = (float*)malloc(frameCount * DAW_CHANNELS * sizeof(float));
    
    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(&decoder, pBuffer, frameCount, &framesRead);

    AudioTrack* newTrack = &engine->tracks[engine->track_count];
    newTrack->pSampleData = pBuffer;
    newTrack->total_frames = (ma_uint32)framesRead;
    newTrack->volume = 0.8f; // default volume
    newTrack->track_offset = 0; // place audio at the beginning of the timeline
    newTrack->is_muted = false;
    snprintf(newTrack->name, 64, "Track %d", engine->track_count + 1);

    engine->track_count++;

    ma_decoder_uninit(&decoder);
    return true;
}

void OpenFileDialogAudio() {
    nfdchar_t *outPath = NULL;
    // filter for audio files
    nfdfilteritem_t filterItem[3] = { { "Audio Files", "wav,mp3,flac" }, { "WAV", "wav" }, { "MP3", "mp3" } };
    
    // open file dialogue (for any OS)
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 3, NULL);

    if (result == NFD_OKAY) {
        printf("Success! Loading: %s\n", outPath);

        // add audio as track
        AddTrackFromFile(&g_Engine, outPath);

        // free path memory allocated by nfd
        NFD_FreePath(outPath);
    } 
    else if (result == NFD_CANCEL) {
        printf("User pressed cancel.\n");
    } 
    else {
        printf("Error: %s\n", NFD_GetError());
    }
}