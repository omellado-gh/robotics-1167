#include "collision.h"
#include "config.h"

void check_camera_collision(Camera *camera) {

    if (camera->position.y < 1.0f) {
        camera->position.y = 1.0f;
    }
    if (camera->position.y > SIZE_WORLD) {
        camera->position.y = SIZE_WORLD;
    }

    if (camera->position.x > SIZE_WORLD) {
        camera->position.x = SIZE_WORLD;
    }

    if (camera->position.x < -SIZE_WORLD) {
        camera->position.x = -SIZE_WORLD;
    }

    if (camera->position.z > SIZE_WORLD) {
        camera->position.z = SIZE_WORLD;
    }

    if (camera->position.z < -SIZE_WORLD) {
        camera->position.z = -SIZE_WORLD;
    }
}