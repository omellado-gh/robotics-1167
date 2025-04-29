#include <ball.h>
#include <config.h>

#include <stdlib.h>
ball_t* create_ball() {
    ball_t *ball = (ball_t *)malloc(sizeof(ball_t));
    if (ball == NULL) {
        fprintf(stderr, "Error allocating memory for ball\n");
        return NULL;
    }

    ball->sphere = create_sphere(RADIUS_BALL, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 0.0f, 0.0f }, WHITE);
    ball->position = &(ball->sphere->object.position);
    ball->velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    ball->visible = false;
    ball->t = 0.0f;

    return ball;
}

void destroy_ball(ball_t *ball) {
    destroy_sphere(ball->sphere);
    free(ball);
}

void draw_ball(ball_t *ball) {
    if (!ball->visible) return;
    draw_sphere(*(ball->sphere));
}

void update_ball(ball_t *ball) {
    if (!ball->visible) return;

    float dt = GetFrameTime();
    ball->t += dt;

    if (ball->t > ball->fly_time) {
        ball->visible = false;
        ball->t = 0.0f;
        return;
    }

    Vector3 *position = ball->position;

    position->x += ball->velocity.x * dt;
    position->z += ball->velocity.z * dt;

    ball->velocity.y += -GRAVITY * dt;
    position->y += ball->velocity.y * dt;
    
}