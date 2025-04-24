#include <robot.h>
#include <random.h>
#include <config.h>
#include <collision.h>
#include <graphics.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raymath.h>

void draw_world(Model *aro) {
    // cancha
    DrawCubeV((Vector3){ 0.0f, -0.05f, 0.0f }, (Vector3){CANCHA_HEIGHT + 0.2f, 0.03f, CANCHA_WIDTH + 0.2f}, RED);
    DrawCubeV((Vector3){ 0.0f, -0.025f, 0.0f }, (Vector3){CANCHA_HEIGHT, 0.05f, CANCHA_WIDTH}, GRAY);
    DrawPlane((Vector3){0.0f, 0.0001f, 0.0f}, (Vector2){0.03f, 9.8f}, WHITE);
    DrawCylinder((Vector3){0.0f, -0.099f, 0.0f}, 0.5f, 0.5f, 0.1f, 32, RED);
    DrawCylinder((Vector3){0.0f, -0.098f, 0.0f}, 0.2f, 0.5f, 0.1f, 32, WHITE);

    // paredes
    DrawCubeV((Vector3){ (CANCHA_HEIGHT / 2.0f) + 0.1f, 0.2f - 0.05f, 0.0f }, (Vector3){0.04f, 0.4f, CANCHA_WIDTH + 0.2f}, GRAY);

    // aros
    DrawCubeV((Vector3){ 9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, RED);
    DrawCubeV((Vector3){ 9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, (Vector3){ 8.74f, 1.3f, 0.0f }, 1.0f, WHITE);

    DrawCubeV((Vector3){ -9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, BLUE);
    DrawCubeV((Vector3){ -9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, (Vector3){ -8.74f, 1.3f, 0.0f }, 1.0f, WHITE);
}

int main() {
    srand((unsigned int)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dron");

    Camera3D camera = { 0 };
    // generar el modelo de un aro
    Mesh aro = GenMeshTorus(0.001f, 0.5f, 32, 32);
    Model aro_m = LoadModelFromMesh(aro);
    aro_m.transform = MatrixRotateX(90.0f * DEG2RAD);

    camera.position = (Vector3){ 10.0f, 0.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    uniciclo_t **robots_red = (uniciclo_t **)malloc(sizeof(uniciclo_t *) * N_ROBOTS_PER_TEAM);
    // uniciclo_t **robots_blue = (uniciclo_t **)malloc(sizeof(uniciclo_t *) * N_ROBOTS_PER_TEAM);
    for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
        robots_red[i] = create_robot((Vector3){0.0f, 0.0f, 0.0f}, RED);
        // robots_blue[i] = create_robot((Vector3){0.0f, 0.0f, 0.0f}, BLUE);
    }

    DisableCursor();

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_SPACE)) {
            camera.position.y += 2.0f * GetFrameTime();
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.position.y -= 2.0f * GetFrameTime();
        }

        check_camera_collision(&camera);

        for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
            move_robot(robots_red[i]);
            // move_robot(robots_blue[i]);
        }

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
            draw_world(&aro_m);

            for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
                draw_robot(robots_red[i]);
                // draw_robot(robots_blue[i]);
            }

            EndMode3D();

            // Draw fps in the top right corner
            DrawFPS(SCREEN_WIDTH - 100, 10);
        EndDrawing();
    }

    for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
        destroy_robot(robots_red[i]);
        // destroy_robot(robots_blue[i]);
    }

    free(robots_red);
    // free(robots_blue);

    UnloadModel(aro_m);
    CloseWindow();

    return 0;
}
