#include <utils.h>
#include <stdio.h>

float get_angle_diff(float current_angle, float new_angle) {
    current_angle += ((2 * PI) * (float)(current_angle < 0)) - ((2 * PI) * (float)(current_angle > 2 * PI));

    if (new_angle > PI) new_angle -= 2 * PI;

    float angle_diff = new_angle - current_angle;
    
    // Ajustar para tomar el camino más corto (ej: 350° -> 10° debe ser -20°, no +340°)
    if (angle_diff > PI) angle_diff -= 2 * PI;
    else if (angle_diff < -PI) angle_diff += 2 * PI;

    return angle_diff;
}

float get_target_angle(Vector3 position, Vector3 target) {
    Vector3 relative_target = Vector3Subtract(target, position);

    float sum = 0.0f;
    if (relative_target.x < 0.0f && relative_target.z < 0.0f)
        sum = PI;
    else if (relative_target.x < 0.0f && relative_target.z > 0.0f)
        sum = 2 * PI;
    else if (relative_target.x > 0.0f && relative_target.z < 0.0f)
        sum = PI;

    float angle = atanf(relative_target.x / relative_target.z);

    return angle + sum;
}


float get_shot_velocity(float distance) {
    return sqrtf(GRAVITY * distance);
}

float get_shot_angle(float distance, float velocity, float h) {

    float gravity = -GRAVITY;
    float solutions[2] = { 0 };

    float a = (gravity * distance) / (2 * velocity * velocity);

    float det = (h / (a * distance)) - 1 + (1 / (4 * a * a));

    if (det < 0) {
        printf("Error no hay solucion real\n");
        return -1.0f;
    }
    float b = -1 / (2 * a);
    float c = sqrtf(det);
    solutions[0] = atanf(b + c);
    solutions[1] = atanf(b - c);

    if (solutions[0] < solutions[1]) return solutions[0];

    return solutions[1];
}