#include <collision.h>
#include <config.h>
#include <random.h>

#include <raymath.h>

void check_camera_collision(Camera *camera) {
    if (camera->position.y < 0.0f)
        camera->position.y = 0.0f;

    if (camera->position.y > WORLD_HEIGHT)
        camera->position.y = WORLD_HEIGHT;

    if (camera->position.x > WORLD_HEIGHT)
        camera->position.x = WORLD_HEIGHT;

    if (camera->position.x < -WORLD_HEIGHT)
        camera->position.x = -WORLD_HEIGHT;

    if (camera->position.z > WORLD_HEIGHT)
        camera->position.z = WORLD_HEIGHT;

    if (camera->position.z < -WORLD_HEIGHT)
        camera->position.z = -WORLD_HEIGHT;
}

void handle_robot_collision(uniciclo_t *robot) {
    if (CHECK_BIT(robot->config, SHOOTING)) return;

    if (CHECK_BIT(robot->config, ROTATING)) {

        if (!ready_robot_rotation(robot)) return;

        NO_COLLISION(robot->config);
        robot->vl = 3.0f;
        robot->steps = 0.5f;
        return;
    }

    float new_angle = 0.0f;

    if (CHECK_BIT(robot->config, CHECK_COLLISION_X)) {
        uint8_t sense = CHECK_BIT(robot->config, COLLISION_X);
        if (sense) new_angle = 270.0f;
        else       new_angle = 90.0f;
    }
    if (CHECK_BIT(robot->config, CHECK_COLLISION_Z)) {
        uint8_t sense = CHECK_BIT(robot->config, COLLISION_Z);
        if (sense) new_angle = 180.0f;
        else       new_angle = 0.0f;
    }
    new_angle *= DEG2RAD;

    configure_robot_rotation(robot, new_angle);
}