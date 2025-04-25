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

void handle_robot_collision(uniciclo_t *robot) {
    robot->vl = 0.0f;
/*
bits del robot->collision_detected
      0: check collision
      1: if set collision up else collision down
      2: if set collision right else collision left
      3: check collision X
      4: check collision Z
      5: set if is rotating
      6: finish rotation
*/
    float start_angle = 0.0f, end_angle = 360.0f;

    if (CHECK_BIT(robot->collision, CHECK_COLLISION_X)) {
        switch (CHECK_BIT(robot->collision, COLLISION_X)) {
            case 0:
                end_angle = 180.0f;
                break;
            case 1:
                start_angle = 180.0f;
                break;
        }
    }
    if (CHECK_BIT(robot->collision, CHECK_COLLISION_Z)) {
        switch (CHECK_BIT(robot->collision, COLLISION_Z)) {
            case 0:
                start_angle = -90.0f;
                end_angle = 90.0f;
                break;
            case 1:
                start_angle = 90.0f;
                end_angle = 270.0f;
                break;
        }
    }

    NO_COLLISION(robot->collision);
}