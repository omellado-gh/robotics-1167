#ifndef COLLISION_H
#define COLLISION_H

#include <robot.h>

#include <raylib.h>

/*
bits del robot->collision_detected
      0: check collision
      1: if set collision up else collision down
      2: if set collision right else collision left
      3: check collision X
      4: check collision Z
      5: set if is rotating
      6: finish rotation
*/

#define CHECK_COLLISION   (uint8_t)0
#define COLLISION_X       (uint8_t)1
#define COLLISION_Z       (uint8_t)2
#define CHECK_COLLISION_X (uint8_t)3
#define CHECK_COLLISION_Z (uint8_t)4
#define ROTATING          (uint8_t)5
#define FINISH_ROTATION   (uint8_t)6

#define SET_BIT(  bit, pos) (uint8_t)((bit) | (1 << (pos)))
#define UNSET_BIT(bit, pos) (uint8_t)((bit) & (~(1 << (pos))))
#define CHECK_BIT(bit, pos) (uint8_t)(((bit) & (1 << (pos))) >> (pos))

#define NO_COLLISION(bit)    ((bit) &= (uint8_t)(0x00))
#define SET_ROTATING(bit)    ((bit) |= (uint8_t)(SET_BIT(bit, ROTATING)))
#define COLLISION_UP(bit)    ((bit) |= (uint8_t)((SET_BIT(  bit, COLLISION_X)) | (SET_BIT(bit, CHECK_COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_X))))
#define COLLISION_DOWN(bit)  ((bit) |= (uint8_t)((UNSET_BIT(bit, COLLISION_X)) | (SET_BIT(bit, CHECK_COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_X))))
#define COLLISION_RIGHT(bit) ((bit) |= (uint8_t)((SET_BIT(  bit, COLLISION_Z)) | (SET_BIT(bit, CHECK_COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_Z))))
#define COLLISION_LEFT(bit)  ((bit) |= (uint8_t)((UNSET_BIT(bit, COLLISION_Z)) | (SET_BIT(bit, CHECK_COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_Z))))

extern void check_camera_collision(Camera3D *camera);
extern void handle_robot_collision(uniciclo_t *robot);

#endif