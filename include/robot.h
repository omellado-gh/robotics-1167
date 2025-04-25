#ifndef ROBOT_H
#define ROBOT_H

#include <frame.h>

#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct RobotUniciclo {
    frame_t *obj;
    float w;
    float *y_rotation;
    float y_rotation_expected;
    float vl;
    size_t steps;
    uint8_t collision;
    Color team;
} uniciclo_t;

extern uniciclo_t* create_robot(Vector3 pos, Color team);
extern void destroy_robot(uniciclo_t* robot);
extern void move_robot(uniciclo_t* robot);
extern void draw_robot(uniciclo_t *robot);
extern float get_angle_diff(float current_angle, float new_angle);


#endif