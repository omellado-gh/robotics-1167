#include <stdio.h>
#include <raylib.h>

extern float get_w(size_t d, Vector2 x);
extern Vector3 get_v(Vector2 uv, size_t d, float phi);
extern Vector4 get_v_dron(Vector3 uv, float phi, float w);
extern float get_diff_velocity(float velocity);
