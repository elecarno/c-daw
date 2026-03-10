#include "../engine/engine.c"
#include <stdio.h>

int main() {
    #include <stdio.h>

    // ... in main() ...
    FILE* f = fopen("resources/audio/ep4_intro.wav", "rb");
    if (f) {
        printf("Standard fopen found the file!\n");
        fclose(f);
    } else {
        printf("Standard fopen could NOT find the file. Check your relative path!\n");
    }

    // 1. Load the data
    if (!AddTrackFromFile(&g_Engine, "resources/audio/ep4_intro.wav")) {
        printf("Failed to load file!\n");
        return -1;
    }

    // 2. Configure the Device
    // We match the DAW standard we set: 44100Hz, Stereo, f32
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate        = 44100;
    deviceConfig.dataCallback      = mixing_callback; // Your mixing function
    deviceConfig.pUserData         = &g_Engine;       // Pass engine to callback

    ma_device device;
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        return -2;
    }

    // 3. Start the hardware
    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start device.\n");
        ma_device_uninit(&device);
        return -3;
    }

    // 4. Tell the Engine to start processing
    g_Engine.is_playing = true;

    printf("Playing: %s\n", g_Engine.tracks[0].name);
    printf("Press Enter to quit...");
    
    getchar();

    // Cleanup
    ma_device_uninit(&device);
    return 0;
}