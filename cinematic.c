#include "cinematic.h"
#include <raymath.h>

float get_w(size_t d, Vector2 x) {
    return (x.x - x.y) / (float)d;
}

float get_diff_velocity(float velocity) {
    return velocity * GetFrameTime();
}

Vector3 get_v(Vector2 uv, size_t d, float phi) {
    float angle = phi * DEG2RAD; // Grados a radianes
	float add = uv.x + uv.y;
    return (Vector3){
		.x = (add / 2.0f) * cosf(angle),
		.y = (add / 2.0f) * sinf(angle),
        .z = get_w(d, uv)
    };
}

Vector4 get_v_dron(Vector3 uv, float phi, float w) {
    float angle = phi * DEG2RAD; // Grados a radianes

    return (Vector4) {
        .x = (cosf(angle) * uv.x) - (sinf(angle) * uv.y),
        .y = (sinf(angle) * uv.x) + (cosf(angle) * uv.y),
        .z = (uv.z),
        .w = (w)
    };
}
