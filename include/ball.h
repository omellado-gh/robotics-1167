#ifndef BALL_H
#define BALL_H

#include <graphics.h>

typedef struct Ball {
    Vector3 *position;
    Vector3 velocity;
    bool visible;
    sphere_t *sphere;
} ball_t;

extern ball_t* create_ball();
extern void destroy_ball(ball_t *ball);
extern void draw_ball(ball_t *ball);
extern void update_ball(ball_t *ball);
#endif
