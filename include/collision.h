#ifndef COLLISION_H
#define COLLISION_H

#include <robot.h>

#include <raylib.h>

#define COLLISION         (uint8_t)0
#define COLLISION_X       (uint8_t)1
#define COLLISION_Z       (uint8_t)2
#define CHECK_COLLISION_X (uint8_t)3
#define CHECK_COLLISION_Z (uint8_t)4

#define NO_COLLISION(bit)    ((bit) &= (uint8_t)(~0x1f))
#define COLLISION_UP(bit)    ((bit) |= (uint8_t)((SET_BIT(  bit, COLLISION_X)) | (SET_BIT(bit, COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_X))))
#define COLLISION_DOWN(bit)  ((bit) |= (uint8_t)((UNSET_BIT(bit, COLLISION_X)) | (SET_BIT(bit, COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_X))))
#define COLLISION_RIGHT(bit) ((bit) |= (uint8_t)((SET_BIT(  bit, COLLISION_Z)) | (SET_BIT(bit, COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_Z))))
#define COLLISION_LEFT(bit)  ((bit) |= (uint8_t)((UNSET_BIT(bit, COLLISION_Z)) | (SET_BIT(bit, COLLISION)) | (SET_BIT(bit, CHECK_COLLISION_Z))))

extern void check_camera_collision(Camera3D *camera);
extern void handle_robot_collision(uniciclo_t *robot);

#endif