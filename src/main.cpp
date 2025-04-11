#include "raylib.h"
#include <cmath>

#define N 32
#define M 64

Vector3 point_on_sphere(float radius, float theta, float phi) {
    Vector3 pos;
    pos.x = radius * sinf(theta) * cosf(phi);
    pos.y = radius * cosf(theta);
    pos.z = radius * sinf(theta) * sinf(phi);
    return pos;
}

int countTheNeighbors(int grid[N][M], int theta, int phi)  
{  
    int livingNeighborCount = 0;
    int neighTheta[8] = {theta-1, theta, theta+1, theta-1, theta+1, theta-1, theta, theta+1};
    int neighPhi[8] = {phi-1, phi-1, phi-1, phi, phi, phi+1, phi+1, phi+1};

    for(int i = 0; i < 8; ++i)  
    {
        int nx = (neighTheta[i] + N) % N;
        int ny = (neighPhi[i] + M) % M;
        if (grid[nx][ny] == 1)
            livingNeighborCount++;
    }

    return livingNeighborCount;
}

void updateLifeGrid(int grid[N][M]) {
    int newGrid[N][M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int neighbors = countTheNeighbors(grid, i, j);
            if(grid[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                newGrid[i][j] = 0;
            else if(neighbors == 3 && grid[i][j] == 0)
                newGrid[i][j] = 1;
            else
                newGrid[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Game of Life on Sphere");

    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    int lifeGrid[N][M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            lifeGrid[i][j] = rand() % 2;
        }
    }

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        float dTheta = PI / N;
        float dPhi = 2 * PI / M;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (lifeGrid[i][j] == 1) {
                    float theta = dTheta * i;
                    float phi = dPhi * j;
                    Vector3 p = point_on_sphere(2.0f, theta, phi);
                    DrawSphere(p, 0.05f, BLACK);
                }
            }
        }

        EndMode3D();

        DrawText("Conway's Game of Life on Sphere", 10, 10, 20, DARKGRAY);

        EndDrawing();

        updateLifeGrid(lifeGrid);
    }

    CloseWindow();
    return 0;
}
