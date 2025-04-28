#ifndef ROBOT_H
#define ROBOT_H

#include <frame.h>

#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

/*
bits del robot->config
      0: set if is collision
      1: if set collision up else collision down
      2: if set collision right else collision left
      3: check collision X
      4: check collision Z
      5: set if is rotating
      6: set if is shooting
      7: set if is launching
*/

#define ROTATING             (uint8_t)5
#define SHOOTING             (uint8_t)6
#define LAUNCHING            (uint8_t)7

#define    SET_BIT(bit, pos) (uint8_t)((bit) | (1 << (pos)))
#define  UNSET_BIT(bit, pos) (uint8_t)((bit) & (~(1 << (pos))))
#define  CHECK_BIT(bit, pos) (uint8_t)(((bit) & (1 << (pos))) >> (pos))

#define    SET_ROTATING(bit) ((bit) |= (uint8_t)(SET_BIT(bit,   ROTATING)))
#define  UNSET_ROTATING(bit) ((bit) &= (uint8_t)(UNSET_BIT(bit, ROTATING)))
#define    SET_SHOOTING(bit) ((bit) |= (uint8_t)(SET_BIT(bit,   SHOOTING)))
#define  UNSET_SHOOTING(bit) ((bit) &= (uint8_t)(UNSET_BIT(bit, SHOOTING)))
#define   SET_LAUNCHING(bit) ((bit) |= (uint8_t)(SET_BIT(bit,   LAUNCHING)))
#define UNSET_LAUNCHING(bit) ((bit) &= (uint8_t)(UNSET_BIT(bit, LAUNCHING)))

typedef struct RobotUniciclo {
    frame_t *obj;
    float w;
    float old_w;
    float *y_rotation;
    float y_rotation_expected;
    float old_y_rotation;
    float vl;
    float old_vl;
    size_t steps;
    uint8_t config;
    float time_to_shot;
    float wait_for_shot;
    void *ball;
    Vector3 target;
    Color team;
} uniciclo_t;

extern uniciclo_t* create_robot(Vector3 pos, Color team);
extern void destroy_robot(uniciclo_t* robot);
extern void update_robot(uniciclo_t* robot);
extern void rotate_robot(uniciclo_t* robot);
extern void move_robot(uniciclo_t* robot);
extern void draw_robot(uniciclo_t *robot);
extern float get_angle_diff(float current_angle, float new_angle);

#endif