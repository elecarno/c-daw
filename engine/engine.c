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
    if (!engine->is_playing) return;

    float* pOut = (float*)pOutput;
    memset(pOut, 0, frameCount * DAW_CHANNELS * sizeof(float));

    for (int t = 0; t < engine->track_count; t++) {
        AudioTrack* track = &engine->tracks[t];
        if (track->is_muted) continue;

        for (int c = 0; c < track->clip_count; c++) {
            AudioClip* clip = &track->clips[c];

            for (ma_uint32 i = 0; i < frameCount; i++) {
                ma_uint32 globalFrame = engine->playhead + i;

                if (globalFrame >= clip->timeline_start && 
                    globalFrame < (clip->timeline_start + clip->total_frames)) {
                    
                    ma_uint32 localFrame = globalFrame - clip->timeline_start;

                    pOut[i * 2]     += clip->pSampleData[localFrame * 2] * track->volume;
                    pOut[i * 2 + 1] += clip->pSampleData[localFrame * 2 + 1] * track->volume;
                }
            }
        }
    }
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

bool LoadClipData(const char* filePath, AudioClip* outClip) {
    ma_decoder decoder;
    ma_decoder_config config = ma_decoder_config_init(DAW_FORMAT, DAW_CHANNELS, DAW_SAMPLE_RATE);

    if (ma_decoder_init_file(filePath, &config, &decoder) != MA_SUCCESS) {
        return false;
    }

    ma_uint64 totalFrames;
    ma_decoder_get_length_in_pcm_frames(&decoder, &totalFrames);

    float* pBuffer = (float*)malloc(totalFrames * DAW_CHANNELS * sizeof(float));
    if (pBuffer == NULL) {
        ma_decoder_uninit(&decoder);
        return false;
    }

    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(&decoder, pBuffer, totalFrames, &framesRead);

    outClip->pSampleData = pBuffer;
    outClip->total_frames = (ma_uint32)framesRead;
    outClip->timeline_start = 0; // Default to start of timeline
    
    // Extract filename for the clip name
    const char* fileName = strrchr(filePath, '\\'); // Windows
    if (!fileName) fileName = strrchr(filePath, '/'); // Unix
    snprintf(outClip->name, 64, "%s", fileName ? fileName + 1 : filePath);

    ma_decoder_uninit(&decoder);
    return true;
}

// The main function called by your File Dialog
bool ImportFileAsNewTrack(DAWEngine* engine, const char* filePath) {
    if (engine->track_count >= 16) return false;

    // 1. Initialize the new track
    AudioTrack* newTrack = &engine->tracks[engine->track_count];
    newTrack->clip_count = 0;
    newTrack->volume = 0.8f;
    newTrack->is_muted = false;
    snprintf(newTrack->name, 64, "Track %d", engine->track_count + 1);

    // 2. Load the file into the first clip slot of this track
    if (!LoadClipData(filePath, &newTrack->clips[newTrack->clip_count])) {
        return false;
    }

    newTrack->clip_count++;
    engine->track_count++;
    
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
        ImportFileAsNewTrack(&g_Engine, outPath);

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