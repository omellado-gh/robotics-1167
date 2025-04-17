#include "dron.h"
#include "config.h"

#include <raylib.h>
#include <math.h>
#include <rcamera.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dron");

    Camera3D camera = { 0 };

    camera.position = (Vector3){ 32.0f, 12.0f, 32.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int camera_mode = CAMERA_FIRST_PERSON;

    Model model = LoadModel("resources/models/Drone_Costum/Material/drone_costum.obj");

    Vector3 position = { 0.0f, 30.0f, 0.0f };
    Vector3 velocity = { 0.0f, 0.0f, 0.0f };

    // gravity
    float gravity = -9.81f * 100;

    bool touching_ground = false;

    float total_time = 0.0f;
    DisableCursor();

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        // Update
        // simulate the gravity

        if (!touching_ground) {
            float dt = GetFrameTime();
            total_time += dt;
            position.y += velocity.y * dt + 0.5f * gravity * pow(dt, 2);

            velocity.y += gravity * dt;

            printf("velocity y: %f\n", velocity.y);

            // ground collision
            if (position.y < 0.0f) {
                position.y = 0.0f;
                touching_ground = true;
            }
        }

        printf("touching ground: %d\nlast velocity: %f\ntotal time: %f\n", touching_ground, velocity.y, total_time);

        // UpdateCamera(&camera, camera_mode);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 64.0f }, LIGHTGRAY);

            DrawModel(model, position, 0.3f, WHITE);

            EndMode3D();


            DrawRectangle(0, 0, 200, 100, RED);

            // Draw fps in the top right corner
            DrawFPS(SCREEN_WIDTH - 100, 10);
        EndDrawing();
    }

    UnloadModel(model); // Unload model

    CloseWindow();

    return 0;
}
