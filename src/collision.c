#include <collision.h>
#include <config.h>

void check_camera_collision(Camera *camera) {

    if (camera->position.y < 0.0f) {
        camera->position.y = 0.0f;
    }
    if (camera->position.y > WORLD_HEIGHT) {
        camera->position.y = WORLD_HEIGHT;
    }

    if (camera->position.x > WORLD_HEIGHT) {
        camera->position.x = WORLD_HEIGHT;
    }

    if (camera->position.x < -WORLD_HEIGHT) {
        camera->position.x = -WORLD_HEIGHT;
    }

    if (camera->position.z > WORLD_HEIGHT) {
        camera->position.z = WORLD_HEIGHT;
    }

    if (camera->position.z < -WORLD_HEIGHT) {
        camera->position.z = -WORLD_HEIGHT;
    }
}