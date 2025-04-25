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
        if (*(robot->y_rotation) < 0) *(robot->y_rotation) += 2 * PI;
        if (fabsf(robot->y_rotation_expected - robot->obj->rotation.y) > 1.0f) {
            // printf("Girando el robot, orientación: %f, orientación esperada: %f\n", robot->obj->rotation.y, robot->y_rotation_expected);
            *(robot->y_rotation) += robot->w * 5.0f * GetFrameTime();
            return;
        }
        *(robot->y_rotation) = robot->y_rotation_expected;
        NO_COLLISION(robot->collision);
        robot->vl = 3.0f;
        robot->w = 0.0f;
        robot->steps = 200;
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

    if (new_angle > PI) new_angle -= 2 * PI;

    if (*(robot->y_rotation) < 0) *(robot->y_rotation) += 2 * PI;
    printf("robot->y_rotation: %f, new_angle: %f,", *(robot->y_rotation) * RAD2DEG, new_angle * RAD2DEG);

    // 2. Calcular diferencia de ángulo más corta (considerando wraparound)
    float angle_diff = new_angle - *(robot->y_rotation);
    
    // Ajustar para tomar el camino más corto (ej: 350° -> 10° debe ser -20°, no +340°)
    if (angle_diff > PI) angle_diff -= 2 * PI;
    else if (angle_diff < -PI) angle_diff += 2 * PI;

    printf(", angle_diff: %f\n", angle_diff * RAD2DEG);

    robot->w = angle_diff / fabsf(angle_diff);
}