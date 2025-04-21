#include <robot.h>
#include <config.h>
#include <collision.h>
#include <graphics.h>
#include <cinematic.h>

#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>

void draw_world(Model *aro) {
    // cancha
    DrawCubeV((Vector3){ 0.0f, -0.05f, 0.0f }, (Vector3){CANCHA_HEIGHT + 0.2f, 0.03f, CANCHA_WIDTH + 0.2f}, RED);
    DrawCubeV((Vector3){ 0.0f, -0.025f, 0.0f }, (Vector3){CANCHA_HEIGHT, 0.05f, CANCHA_WIDTH}, GRAY);
    DrawPlane((Vector3){0.0f, 0.0001f, 0.0f}, (Vector2){0.03f, 9.8f}, WHITE);
    DrawCylinder((Vector3){0.0f, -0.099f, 0.0f}, 0.5f, 0.5f, 0.1f, 32, RED);
    DrawCylinder((Vector3){0.0f, -0.098f, 0.0f}, 0.2f, 0.5f, 0.1f, 32, WHITE);

    // aros
    DrawCubeV((Vector3){ 9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, RED);
    DrawCubeV((Vector3){ 9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, (Vector3){ 8.74f, 1.3f, 0.0f }, 1.0f, WHITE);

    DrawCubeV((Vector3){ -9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, BLUE);
    DrawCubeV((Vector3){ -9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, (Vector3){ -8.74f, 1.3f, 0.0f }, 1.0f, WHITE);
}

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dron");

    Camera3D camera = { 0 };
    // generar el modelo de un aro
    Mesh aro = GenMeshTorus(0.001f, 0.5f, 32, 32);
    Model aro_m = LoadModelFromMesh(aro);
    aro_m.transform = MatrixRotateX(90.0f * DEG2RAD);

    camera.position = (Vector3){ 16.0f, 6.0f, 16.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

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

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

            draw_world(&aro_m);

            EndMode3D();

            // Draw fps in the top right corner
            DrawFPS(SCREEN_WIDTH - 100, 10);
        EndDrawing();
    }

    UnloadModel(aro_m);
    CloseWindow();

    return 0;
}
