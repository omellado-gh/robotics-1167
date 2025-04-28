#include <utils.h>


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
