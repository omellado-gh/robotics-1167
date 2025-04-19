#include "dron.h"
#include "config.h"
#include "collision.h"
#include "graphics.h"
#include "cinematic.h"

#include <stdio.h>
#include <stdlib.h>


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dron");

    Camera3D camera = { 0 };

    camera.position = (Vector3){ 16.0f, 6.0f, 16.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int camera_mode = CAMERA_FIRST_PERSON;

    DisableCursor();

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_SPACE)) {
            camera.position.y += get_diff_velocity(2.0f);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.position.y -= get_diff_velocity(2.0f);
        }

        check_camera_collision(&camera);

        UpdateCamera(&camera, camera_mode);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            DrawGrid(64, 1.0f);



            EndMode3D();

            DrawRectangle(0, 0, 200, 100, WHITE);

            // Draw fps in the top right corner
            DrawFPS(SCREEN_WIDTH - 100, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
