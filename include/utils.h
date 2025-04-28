#ifndef UTILS_H
#define UTILS_H

#include <config.h>

#include <raymath.h>

float get_angle_diff(float current_angle, float new_angle);
float get_target_angle(Vector3 position, Vector3 target);
float get_shot_velocity(float distance);
float get_shot_angle(float distance, float velocity, float h);

#endif