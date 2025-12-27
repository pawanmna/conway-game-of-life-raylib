#include "raylib.h"
#include "GameOfLife.h"
#include "Constants.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Vector3 PointOnSphere(float radius, float theta, float phi) {
    Vector3 pos;
    pos.x = radius * sinf(theta) * cosf(phi);
    pos.y = radius * cosf(theta);
    pos.z = radius * sinf(theta) * sinf(phi);
    return pos;
}

int main() {
    InitWindow(GameConstants::ScreenWidth, GameConstants::ScreenHeight, "Game of Life on Sphere");
    
    srand(static_cast<unsigned int>(time(NULL)));

    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    GameOfLife game;
    bool paused = false;
    float updateTimer = 0.0f;
    float updateInterval = 0.1f; // Update every 0.1 seconds

    while (!WindowShouldClose()) {
        // Input Handling
        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }
        if (IsKeyPressed(KEY_R)) {
            game.Reset();
        }

        // Update Logic
        UpdateCamera(&camera, CAMERA_ORBITAL);

        if (!paused) {
            updateTimer += GetFrameTime();
            if (updateTimer >= updateInterval) {
                game.Update();
                updateTimer = 0.0f;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        float dTheta = PI / GameConstants::GridRows;
        float dPhi = 2 * PI / GameConstants::GridCols;

        for (int i = 0; i < GameConstants::GridRows; ++i) {
            for (int j = 0; j < GameConstants::GridCols; ++j) {
                if (game.IsAlive(i, j)) {
                    float theta = dTheta * i;
                    float phi = dPhi * j;
                    Vector3 p = PointOnSphere(GameConstants::SphereRadius, theta, phi);
                    DrawSphere(p, 0.05f, BLACK);
                }
            }
        }
        
        DrawSphereWires((Vector3){0,0,0}, GameConstants::SphereRadius, 16, 16, Fade(LIGHTGRAY, 0.3f));

        EndMode3D();

        DrawText("Conway's Game of Life on Sphere", 10, 10, 20, DARKGRAY);
        DrawText("Controls: SPACE to Pause, R to Reset", 10, 40, 10, GRAY);
        if (paused) DrawText("PAUSED", 10, 60, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
