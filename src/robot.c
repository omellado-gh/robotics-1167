#include <robot.h>
#include <config.h>
#include <random.h>
#include <objects.h>
#include <collision.h>
#include <utils.h>

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

void restart_robot(uniciclo_t *robot, float start_angle, float end_angle) {
    float new_angle = get_random_float(start_angle * DEG2RAD, end_angle * DEG2RAD);
    float angle_diff = get_angle_diff(*(robot->y_rotation), new_angle);

    robot->steps = get_random_float(0.2f, 1.0f);
    robot->w = angle_diff / robot->steps;
    robot->vl = get_random_float(0.0f, 6.0f);
}


uniciclo_t* create_robot(Vector3 pos, Color color) {

    uniciclo_t* robot = (uniciclo_t*)malloc(sizeof(uniciclo_t));

    bool team = color.r == RED.r && color.g == RED.g && color.b == RED.b;
    Vector3 target = { 0 };
    if (team) target = POS_RING_BLUE;
    else target = POS_RING_RED;
    frame_t *frame = create_frame(pos, (Vector3){0.0f, 0.0f, 0.0f});
    generate_frame(frame, color);

    ball_t *ball = create_ball();

    *robot = (uniciclo_t) {
        .obj = frame,
        .vl = 0.0f,
        .steps = 0,
        .team = color,
        .y_rotation = &frame->rotation.y,
        .y_rotation_expected = -1.0f,
        .time_to_shot = get_random_float(5.0f, 10.0f),
        .wait_for_shot = WAIT_TIME_FOR_SHOT,
        .target = target,
        .ball = ball,
        .config = 0,
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
    destroy_ball(robot->ball);
    free(robot);
}


void draw_robot(uniciclo_t *robot) {
    if (robot == NULL || robot->obj == NULL)
        return;

    draw_frame(robot->obj);
    draw_ball(robot->ball);
}

void rotate_robot(uniciclo_t *robot) {
    float y_rotation = *(robot->y_rotation);
    y_rotation += robot->w * GetFrameTime();

    if (y_rotation > 2 * PI) y_rotation -= 2 * PI;
    else if (y_rotation < 0.0f) y_rotation += 2 * PI;

    *(robot->y_rotation) = y_rotation;
}

void move_robot(uniciclo_t *robot) {
    if (CHECK_BIT(robot->config, SHOOTING)) return;
    if (CHECK_BIT(robot->config, COLLISION)) return;

    float y_rotation = *(robot->y_rotation);
    float *x = &robot->obj->position.x;
    float *z = &robot->obj->position.z;

    robot->steps -= GetFrameTime();
    if (robot->steps < 0) {
        restart_robot(robot, 0.0f, 360.0f);
        return;
    }

    float velocity = robot->vl * GetFrameTime();
    *x += velocity * sinf(y_rotation);
    *z += velocity * cosf(y_rotation);

    if (*x <= -8.7f) {
        *x = -8.7f;
        COLLISION_DOWN(robot->config);
    }
    if (*x >= 8.7f) {
        *x = 8.7f;
        COLLISION_UP(robot->config);
    }
    if (*z <= -4.7f) {
        *z = -4.7f;
        COLLISION_LEFT(robot->config);
    }
    if (*z >= 4.7f) {
        *z = 4.7f;
        COLLISION_RIGHT(robot->config);
    }
}

bool ready_robot_rotation(uniciclo_t *robot) {
    float y_rotation = *(robot->y_rotation);
    if (fabsf(robot->y_rotation_expected - y_rotation) > 0.1f) // rotacion de acercamiento
        return false;

    *(robot->y_rotation) = robot->y_rotation_expected; // correcion de angulo
    robot->w = 0.0f;
    UNSET_ROTATING(robot->config);
    return true;
}

void configure_robot_rotation(uniciclo_t *robot, float rotation_target) {
    SET_ROTATING(robot->config);
    float y_rotation = *(robot->y_rotation);

    robot->w = 5.0f;

    robot->y_rotation_expected = rotation_target;
    float angle_diff = get_angle_diff(y_rotation, rotation_target);
    if (angle_diff < 0.0f) robot->w = -robot->w;
}

void launch_ball(uniciclo_t *robot) {

    Vector3 target = {
        robot->target.x,
        0.0f,
        robot->target.z
    };

    float h = robot->target.y;
    float distance = Vector3Distance(robot->obj->position, target);
    printf("distance: %f\n", distance);
    float velocity = get_shot_velocity(distance);
    printf("velocity: %f\n", velocity);
    float angle = get_shot_angle(distance, velocity, h);
    printf("angle: %f\n", angle * RAD2DEG);

    float y_rotation = *(robot->y_rotation);

    Vector3 velocity_vector = { 0 };
    float horizontal_velocity = velocity * cosf(angle);
    velocity_vector.y = velocity * sinf(angle),
    velocity_vector.x = horizontal_velocity * sinf(y_rotation);
    velocity_vector.z = horizontal_velocity * cosf(y_rotation);

    robot->ball->fly_time = (distance / horizontal_velocity) + 0.1f;
    robot->ball->visible = true;
    *(robot->ball->position) = robot->obj->position;
    robot->ball->velocity = velocity_vector;
}

void handle_shot(uniciclo_t *robot) {
    if (!CHECK_BIT(robot->config, SHOOTING)) {
        SET_SHOOTING(robot->config);
        robot->old_w = robot->w;
        robot->old_y_rotation = *(robot->y_rotation);
        float rotation_target = get_target_angle(robot->obj->position, robot->target);
        configure_robot_rotation(robot, rotation_target);
    }

    if (CHECK_BIT(robot->config, ROTATING) && !CHECK_BIT(robot->config, LAUNCHING)) {
        if (!ready_robot_rotation(robot)) return;
        SET_LAUNCHING(robot->config);
    }

    if (!CHECK_BIT(robot->config, LAUNCHING)) return;

    if (!CHECK_BIT(robot->config, ROTATING)) {
        robot->wait_for_shot -= GetFrameTime();
        if (robot->wait_for_shot > 0) return;
        robot->wait_for_shot = WAIT_TIME_FOR_SHOT;

        launch_ball(robot);

        // rotar el robot al angulo original
        configure_robot_rotation(robot, robot->old_y_rotation);
    }

    if (!ready_robot_rotation(robot)) return;
    robot->time_to_shot = get_random_float(5.0f, 10.0f);
    robot->w = robot->old_w;

    UNSET_LAUNCHING(robot->config);
    UNSET_SHOOTING(robot->config);
}

void update_robot(uniciclo_t *robot) {
    if (robot == NULL) return;

    if (robot->time_to_shot > 0) robot->time_to_shot -= GetFrameTime();

    if (CHECK_BIT(robot->config, SHOOTING) || robot->time_to_shot < 0)
        handle_shot(robot);

    if (CHECK_BIT(robot->config, COLLISION))
        handle_robot_collision(robot);

    rotate_robot(robot);
    move_robot(robot);
    if (!robot->ball->visible) return;
    update_ball(robot->ball);
}