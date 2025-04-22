#include <robot.h>
#include <config.h>
#include <random.h>
#include <objects.h>

#include <raymath.h>
#include <stdlib.h>


void generate_frame(frame_t *frame, Color team) {
    if (frame == NULL) {
        return;
    }

    // create the robot
    cylinder_t *base = create_cylinder(0.15f, 0.10f, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, team);
    add_entity(frame, base, true);

    cylinder_t *head = create_cylinder(0.08f, 0.04f, (Vector3){0.0f, 0.13f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, WHITE);
    add_entity(frame, head, true);
}


uniciclo_t* create_robot(Vector3 pos, Color team) {

    uniciclo_t* robot = (uniciclo_t*)malloc(sizeof(uniciclo_t));

    frame_t *frame = create_frame(pos, (Vector3){0.0f, 0.0f, 0.0f});
    generate_frame(frame, team);
    *robot = (uniciclo_t) {
        .obj = frame,
        .vl = 0.0f,
        .steps = 0,
        .team = team,
        .w = 0.0f
    };

    return robot;
}

void delete_robot(uniciclo_t* robot) {
    destroy_frame(robot->obj);
    free(robot);
}

void restart_robot(uniciclo_t *robot) {
    float new_angle = get_random_float(-180.0f, 180.0f) * DEG2RAD;
    robot->steps = get_random_size_t(10, 200);
    robot->w = (new_angle - robot->obj->rotation.y) / (float)robot->steps;
    robot->vl = get_random_float(0.0f, 6.0f);
}

void move_robot(uniciclo_t *robot) {

    robot->obj->rotation.y += robot->w;

    robot->obj->position.x += robot->vl * cosf(robot->obj->rotation.y) * GetFrameTime();
    robot->obj->position.z += robot->vl * sinf(robot->obj->rotation.y) * GetFrameTime();

    robot->steps -= 1;
    if (robot->steps == 0)
        restart_robot(robot);

    if (robot->obj->position.x <= -8.7f) {
        robot->obj->position.x = -8.7f;
        robot->steps = 0;
    }
    if (robot->obj->position.x >= 8.7f) {
        robot->obj->position.x = 8.7f;
        robot->steps = 0;
    }
    if (robot->obj->position.z <= -4.7f) {
        robot->obj->position.z = -4.7f;
        robot->steps = 0;
    }
    if (robot->obj->position.z >= 4.7f) {
        robot->obj->position.z = 4.7f;
        robot->steps = 0;
    }
}