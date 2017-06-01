/*******************************************************************************************
*
*   raylib [shaders] example - Apply a shader to a 3d model (adapted for HTML5 platform)
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

// Define the camera to look into our 3d world
Camera camera = {{ 3.0f, 3.0f, 3.0f }, { 0.0f, 1.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f };

Model dwarf;         // OBJ model
Texture2D texture;   // Model texture
Shader shader;       // Postpro shader

Vector3 position = { 0.0f, 0.0f, 0.0f };  // Set model position

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - model shader");

    dwarf = LoadModel("resources/model/dwarf.obj");                  // Load OBJ model
    texture = LoadTexture("resources/model/dwarf_diffuse.png");      // Load model texture
    shader = LoadShader("resources/shaders/glsl100/base.vs", 
                        "resources/shaders/glsl100/grayscale.fs");   // Load model shader

    dwarf.material.shader = shader;             // Set shader effect to 3d model
    dwarf.material.texDiffuse = texture;        // Bind texture to model

    // Setup orbital camera
    SetCameraMode(camera, CAMERA_ORBITAL);      // Set an orbital camera mode

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texture);     // Unload texture
    UnloadModel(dwarf);         // Unload model

    rlCloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);              // Update internal camera and our camera
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        Begin3dMode(camera);

            DrawModel(dwarf, position, 2.0f, WHITE);   // Draw 3d model with texture

            DrawGrid(10, 1.0f);     // Draw a grid

        End3dMode();
        
        DrawText("(c) Dwarf 3D model by David Moreno", screenWidth - 200, screenHeight - 20, 10, GRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}