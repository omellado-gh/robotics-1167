#include <robot.h>
#include <config.h>
#include <random.h>
#include <objects.h>
#include <collision.h>

#include <raymath.h>
#include <stdlib.h>

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

float get_angle_diff(float current_angle, float new_angle) {
    current_angle += ((2 * PI) * (float)(current_angle < 0)) - ((2 * PI) * (float)(current_angle > 2 * PI));

    if (new_angle > PI) new_angle -= 2 * PI;

    float angle_diff = new_angle - current_angle;
    
    // Ajustar para tomar el camino más corto (ej: 350° -> 10° debe ser -20°, no +340°)
    if (angle_diff > PI) angle_diff -= 2 * PI;
    else if (angle_diff < -PI) angle_diff += 2 * PI;

    return angle_diff;
}

void restart_robot(uniciclo_t *robot, float start_angle, float end_angle) {
    float new_angle = get_random_float(start_angle * DEG2RAD, end_angle * DEG2RAD);
    float angle_diff = get_angle_diff(*(robot->y_rotation), new_angle);

    robot->steps = get_random_size_t(10, 200);
    robot->w = angle_diff / (float)robot->steps;
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
        .y_rotation = &frame->rotation.y,
        .collision = 0,
        .w = 0.0f
    };

    restart_robot(robot, 0.0f, 360.0f);

    // robot->vl = 2.0f;
    // *(robot->y_rotation) = 89.0f * DEG2RAD;
    // robot->steps = (size_t)0xFFFFFFFFFFFFFFFF;

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

void rotate_robot(uniciclo_t *robot) {
    float y_rotation = *(robot->y_rotation);
    y_rotation += robot->w;

    if (y_rotation > 2 * PI) y_rotation -= 2 * PI;
    else if (y_rotation < 0.0f) y_rotation += 2 * PI;

    *(robot->y_rotation) = y_rotation;
}

void move_robot(uniciclo_t *robot) {

    float y_rotation = *(robot->y_rotation);
    float *x = &robot->obj->position.x;
    float *z = &robot->obj->position.z;

    if (robot->collision & 0x01) {
        handle_robot_collision(robot);
        return;
    }

    robot->steps -= 1;
    if (robot->steps == 0) {
        restart_robot(robot, 0.0f, 360.0f);
        return;
    }

    float velocity = robot->vl * GetFrameTime();

    *x += velocity * sinf(y_rotation);
    *z += velocity * cosf(y_rotation);

    if (*x <= -8.7f) {
        *x = -8.7f;
        COLLISION_DOWN(robot->collision);
    }
    if (*x >= 8.7f) {
        *x = 8.7f;
        COLLISION_UP(robot->collision);
    }
    if (*z <= -4.7f) {
        *z = -4.7f;
        COLLISION_LEFT(robot->collision);
    }
    if (*z >= 4.7f) {
        *z = 4.7f;
        COLLISION_RIGHT(robot->collision);
    }
}

void update_robot(uniciclo_t *robot) {
    if (robot == NULL || robot->obj == NULL)
        return;

    rotate_robot(robot);
    move_robot(robot);
}