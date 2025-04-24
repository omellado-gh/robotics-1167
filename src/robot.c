#include <robot.h>
#include <config.h>
#include <random.h>
#include <objects.h>

#include <raymath.h>
#include <stdlib.h>

/*
bits del robot->collision_detected
      0: check collision
      1: if set collision up else collision down
      2: if set collision right else collision left
*/

#define CHECK_COLLISION (uint8_t)0
#define COLLISION_X     (uint8_t)1
#define COLLISION_Z     (uint8_t)2

#define SET_BIT(bit, pos) (uint8_t)((bit) | (1 << (pos)))
#define UNSET_BIT(bit, pos) (uint8_t)((bit) & (~(1 << (pos))))
#define CHECK_BIT(bit, pos) (uint8_t)(((bit) & (1 << (pos))) >> (pos))

#define NO_COLLISION(bit) ((bit) &= (uint8_t)(~0x07))
#define COLLISION_UP(bit)    ((bit) |= (uint8_t)(SET_BIT(  bit, COLLISION_X) | SET_BIT(bit, CHECK_COLLISION)))
#define COLLISION_DOWN(bit)  ((bit) |= (uint8_t)(UNSET_BIT(bit, COLLISION_X) | SET_BIT(bit, CHECK_COLLISION)))
#define COLLISION_RIGHT(bit) ((bit) |= (uint8_t)(SET_BIT(  bit, COLLISION_Z) | SET_BIT(bit, CHECK_COLLISION)))
#define COLLISION_LEFT(bit)  ((bit) |= (uint8_t)(UNSET_BIT(bit, COLLISION_Z) | SET_BIT(bit, CHECK_COLLISION)))

void generate_frame(frame_t *frame, Color team) {
    if (frame == NULL) {
        return;
    }

    // create the robot

    // body
    cylinder_t *base = create_cylinder(0.15f, 0.10f, (Vector3){0.0f, 0.04f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, team);
    add_entity(frame, base);
    cylinder_t *head = create_cylinder(0.08f, 0.06f, (Vector3){0.0f, 0.14f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, WHITE);
    add_entity(frame, head);

    // wheels
    cylinder_t *r_wheel = create_cylinder(0.08f, 0.02f, (Vector3){0.15f, 0.08f, 0.0f}, (Vector3){0.0f, 0.0f, -90.0f * DEG2RAD}, BLACK);
    add_entity(frame, r_wheel);
    cylinder_t *l_wheel = create_cylinder(0.08f, 0.02f, (Vector3){-0.15f, 0.08f, 0.0f}, (Vector3){0.0f, 0.0f, 90.0f * DEG2RAD}, BLACK);
    add_entity(frame, l_wheel);

    // cannon
    cylinder_t *cannon = create_cylinder(0.03f, 0.2f, (Vector3){0.0f, 0.16f, 0.05f}, (Vector3){80.0f * DEG2RAD, 0.0f, 0.0f}, DARKGRAY);
    add_entity(frame, cannon);
}

void restart_robot(uniciclo_t *robot, float start_angle, float end_angle) {
    float new_angle = get_random_float(start_angle, end_angle) * DEG2RAD;
    robot->steps = get_random_size_t(10, 200);
    robot->w = (new_angle - robot->obj->rotation.y) / (float)robot->steps;
    robot->vl = get_random_float(0.0f, 6.0f);
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
        .collision_detected = 0,
        .w = 0.0f
    };

    restart_robot(robot, 0.0f, 360.0f);

    return robot;
}

void destroy_robot(uniciclo_t* robot) {
    destroy_frame(robot->obj);
    free(robot);
}


void draw_robot(uniciclo_t *robot) {
    if (robot == NULL || robot->obj == NULL)
        return;

    draw_frame(robot->obj);
}

void move_robot(uniciclo_t *robot) {

    if ((robot->collision_detected & 0x01) == 0) {
        robot->steps -= 1;
        if (robot->steps == 0) {
            restart_robot(robot, 0.0f, 360.0f);
            return;
        }

        robot->obj->rotation.y += robot->w;

        robot->obj->position.x += robot->vl * sinf(robot->obj->rotation.y) * GetFrameTime();
        robot->obj->position.z += robot->vl * cosf(robot->obj->rotation.y) * GetFrameTime();


        if (robot->obj->position.x <= -8.7f) {
            robot->obj->position.x = -8.7f;
            COLLISION_DOWN(robot->collision_detected);
        }
        if (robot->obj->position.x >= 8.7f) {
            robot->obj->position.x = 8.7f;
            COLLISION_UP(robot->collision_detected);
        }
        if (robot->obj->position.z <= -4.7f) {
            robot->obj->position.z = -4.7f;
            COLLISION_LEFT(robot->collision_detected);
        }
        if (robot->obj->position.z >= 4.7f) {
            robot->obj->position.z = 4.7f;
            COLLISION_RIGHT(robot->collision_detected);
        }
        return;
    }
    // handle collision
    robot->vl = 0.0f;

/*
bits del robot->collision_detected
      0: check collision
      1: if set collision up else collision down
      2: if set collision right else collision left
*/
    switch (CHECK_BIT(robot->collision_detected, COLLISION_X)) {
        case 0:
            printf("el robot colisiono abajo\n");
            break;
        case 1:
            printf("el robot colisiono arriba\n");
            break;
    }
    switch (CHECK_BIT(robot->collision_detected, COLLISION_Z)) {
        case 0:
            printf("el robot colisiono a la izquierda\n");
            break;
        case 1:
            printf("el robot colisiono a la derecha\n");
            break;
    }

    NO_COLLISION(robot->collision_detected);
}
