#include "frame.h"
#include <raylib.h>

typedef struct Dron {
    Vector3 uv;
    float w;
    Vector3 x;

    Color color;
} dron_t;

extern dron_t *create_dron(Vector3 initial_pos, Color color);
