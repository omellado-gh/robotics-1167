#include <collision.h>
#include <config.h>
#include <random.h>

#include <raymath.h>

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
    if (CHECK_BIT(robot->collision, ROTATING)) {
        *(robot->y_rotation) += ((2 * PI) * (float)(*(robot->y_rotation) < 0)) - ((2 * PI) * (float)(*(robot->y_rotation) > 2 * PI));
        if (fabsf(robot->y_rotation_expected - robot->obj->rotation.y) > 0.1f) {
            *(robot->y_rotation) += robot->w * 5.0f * GetFrameTime();
            return;
        }
        *(robot->y_rotation) = robot->y_rotation_expected;
        NO_COLLISION(robot->collision);
        robot->vl = 3.0f;
        robot->w = 0.0f;
        robot->steps = 50;
        return;
    }

    float new_angle = 0.0f;

    if (CHECK_BIT(robot->collision, CHECK_COLLISION_X)) {
        uint8_t sense = CHECK_BIT(robot->collision, COLLISION_X);
        new_angle = ((270.0f * (float)sense) + (90.0f * (float)((~sense) & 0x01))) * DEG2RAD;
    }
    if (CHECK_BIT(robot->collision, CHECK_COLLISION_Z)) {
        uint8_t sense = CHECK_BIT(robot->collision, COLLISION_Z);
        new_angle = ((180.0f * (float)sense) + (0.0f * (float)((~sense) & 0x01))) * DEG2RAD;
    }
    SET_ROTATING(robot->collision);

    robot->y_rotation_expected = new_angle;

    float angle_diff = get_angle_diff(*(robot->y_rotation), new_angle);

    robot->w = angle_diff / fabsf(angle_diff);
}