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
    DrawCubeV((Vector3){ 0.0f, -0.05f, 0.0f }, (Vector3){CANCHA_HEIGHT + 0.2f, 0.03f, CANCHA_WIDTH + 0.2f}, RED);
    DrawCubeV((Vector3){ 0.0f, -0.025f, 0.0f }, (Vector3){CANCHA_HEIGHT, 0.05f, CANCHA_WIDTH}, GRAY);
    DrawPlane((Vector3){0.0f, 0.0001f, 0.0f}, (Vector2){0.03f, 9.8f}, WHITE);
    DrawCylinder((Vector3){0.0f, -0.099f, 0.0f}, 0.5f, 0.5f, 0.1f, 32, RED);
    DrawCylinder((Vector3){0.0f, -0.098f, 0.0f}, 0.2f, 0.5f, 0.1f, 32, WHITE);

    DrawCubeV((Vector3){ 9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, RED);
    DrawCubeV((Vector3){ 9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, POS_RING_RED, 1.0f, WHITE);

    DrawCubeV((Vector3){ -9.0f, 1.5f, 0.0f }, (Vector3){0.04f, 0.7f, 1.4f}, BLUE);
    DrawCubeV((Vector3){ -9.0f, 0.6f, 0.0f }, (Vector3){0.03f, 1.2f, 0.06f}, WHITE);
    DrawModel(*aro, POS_RING_BLUE, 1.0f, WHITE);
}

int main() {
    srand((unsigned int)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dron");

    Mesh aro = GenMeshTorus(0.001f, 0.5f, 32, 32);
    Model aro_m = LoadModelFromMesh(aro);
    aro_m.transform = MatrixRotateX(90.0f * DEG2RAD);

    Camera3D camera = { 0 };
    camera.position = POS_RING_BLUE;
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    uniciclo_t **robots_red = (uniciclo_t **)malloc(sizeof(uniciclo_t *) * N_ROBOTS_PER_TEAM);
#if !ONCE_TEAM
    uniciclo_t **robots_blue = (uniciclo_t **)malloc(sizeof(uniciclo_t *) * N_ROBOTS_PER_TEAM);
#endif
    for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
        robots_red[i] = create_robot((Vector3){0.0f, 0.0f, 0.0f}, RED);
#if !ONCE_TEAM
        robots_blue[i] = create_robot((Vector3){0.0f, 0.0f, 0.0f}, BLUE);
#endif
    }

    DisableCursor();

    bool fixed_target_camera = false;
    size_t robot_index = 0;
    bool pause = false;
    char team = 'r';

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_P)) pause = !pause;
        if (IsKeyDown(KEY_SPACE)) camera.position.y += 2.0f * GetFrameTime();
        if (IsKeyDown(KEY_LEFT_SHIFT)) camera.position.y -= 2.0f * GetFrameTime();
        if (IsKeyPressed(KEY_F)) fixed_target_camera = !fixed_target_camera;
        if (IsKeyPressed(KEY_T)) team = (team == 'r') ? 'b' : 'r';
        if (IsKeyPressed(KEY_RIGHT)) {
            robot_index++;
            if (robot_index >= N_ROBOTS_PER_TEAM) robot_index = 0;
        }
        if (IsKeyPressed(KEY_LEFT)) {
            robot_index--;
            if (robot_index >= N_ROBOTS_PER_TEAM) robot_index = N_ROBOTS_PER_TEAM - 1;
        }

        if (fixed_target_camera) {
            if (team == 'r') camera.target = robots_red[robot_index]->obj->position;
            if (team == 'b') camera.target = robots_blue[robot_index]->obj->position;
        }

        check_camera_collision(&camera);

        if (!pause) {
            for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
                update_robot(robots_red[i]);
#if !ONCE_TEAM
                update_robot(robots_blue[i]);
#endif
            }
        }

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
            draw_world(&aro_m);

            for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
                draw_robot(robots_red[i]);
#if !ONCE_TEAM
                draw_robot(robots_blue[i]);
#endif
            }

            EndMode3D();
            const char *info_robot = TextFormat("Robot: %zu, equipo: %s\nCamara fijada: %s",
                robot_index, 
                team == 'r' ? "rojo" : "azul", 
                fixed_target_camera ? "si" : "no");

            DrawText(info_robot, 10, 10, 20, WHITE);
            DrawFPS(SCREEN_WIDTH - 100, 10);
        EndDrawing();
    }

    for (size_t i = 0; i < N_ROBOTS_PER_TEAM; i++) {
        destroy_robot(robots_red[i]);
#if !ONCE_TEAM
        destroy_robot(robots_blue[i]);
#endif
    }

    free(robots_red);
#if !ONCE_TEAM
    free(robots_blue);
#endif
    UnloadModel(aro_m);
    CloseWindow();

    return 0;
}
