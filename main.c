// clay and raylib
#define CLAY_IMPLEMENTATION
#include "clay-raylib/clay.h"
#include "clay-raylib/clay_renderer_raylib.c"

// shared data and component/layout headesr
#include "headers/globals.h"
#include "headers/components.h"
#include "headers/layouts.h"

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

int main(void) {
    Clay_Raylib_Initialize(
        1280, 720, // width and height
        "c-DAW", // window title
        FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT //flags
    );

    // get memory allocation
    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(
        clayRequiredMemory, 
        malloc(clayRequiredMemory)
    );

    // initalise clay using memory information
    Clay_Initialize(clayMemory, (Clay_Dimensions) {
       .width = GetScreenWidth(),
       .height = GetScreenHeight()
    }, (Clay_ErrorHandler) { HandleClayErrors });

    // handle fonts
    Font fonts[1];
    fonts[FONT_ID_BODY_16] = LoadFontEx("resources/fonts/Atkinson_Hyperlegible_Next/static/AtkinsonHyperlegibleNext-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[FONT_ID_BODY_16].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    // update loop (per frame)
    while (!WindowShouldClose()) {
        // update dimensions every frame to handle resizing
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        // handle input
        Vector2 mousePosition = GetMousePosition();
        Vector2 scrollDelta = GetMouseWheelMoveV();
        Clay_SetPointerState(
            (Clay_Vector2) { mousePosition.x, mousePosition.y },
            IsMouseButtonDown(0)
        );
        Clay_UpdateScrollContainers(
            true,
            (Clay_Vector2) { scrollDelta.x, scrollDelta.y },
            GetFrameTime()
        );

        // get layout render commands for the ui
        Clay_RenderCommandArray renderCommands = layoutEditor();

        // draw the ui
        BeginDrawing();
        ClearBackground(BLACK); // clear the screen each
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
}