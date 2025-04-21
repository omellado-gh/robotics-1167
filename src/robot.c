#include <robot.h>
#include <cinematic.h>
#include <config.h>

#include <raylib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


uniciclo_t* create_robot(Vector3 pos, float d) {

    uniciclo_t* robot = (uniciclo_t*)malloc(sizeof(uniciclo_t));

    frame_t *frame = create_frame(pos, (Vector3){0.0f, 0.0f, 0.0f});
    *robot = (uniciclo_t) {
        .obj = frame,
        .d = d,
	    .uv = {0, 0},
        .steps = 0,
        .w = 0
    };

    return robot;
}

void delete_robot(uniciclo_t* robot) {
    destroy_frame(robot->obj);
    free(robot);
}

void restart_robot(uniciclo_t *robot) {
    robot->obj->position = (Vector3){0.0f, 0.0f, 0.0f};
    robot->obj->rotation = (Vector3){0.0f, 0.0f, 0.0f};
    robot->steps = 0;
    robot->w = 0;
}

void move_robot(uniciclo_t *robot) {

    Vector3 v = get_v(robot->uv, robot->d, robot->obj->rotation.y);

    robot->v.x = v.x;
    robot->v.y = v.y;
    robot->w   = v.z;

    robot->obj->position.x += 1 * robot->v.x;
    robot->obj->position.z += 1 * robot->v.y;
    robot->obj->rotation.y += 1 * robot->w;

    robot->steps -= 1;
    if (robot->steps == 0)
        restart_robot(robot);

    if (robot->position.x <= -8.70) {
        robot->position.x = -8.70;
        robot->nStep = 0;
    }
    if (robot->pos.x >= -0.50) {
        robot->pos.x = -0.50;
        robot->nStep = 0;
    }
    if (robot->pos.z <= -4.70) {
        robot->pos.z = -4.70;
        robot->nStep = 0;
    }
    if (robot->pos.z >= 4.70) {
        robot->pos.z = 4.70;
        robot->nStep = 0;
    }
}