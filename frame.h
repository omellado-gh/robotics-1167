#include "linked_list.h"

#include <raylib.h>
#include <stdio.h>

// a simple visual python frame implementation
typedef struct Frame {
    Vector3 position;  // 3D coordinates
    float rotation; // angle in degrees
    linked_list_t *entities; // list of models or sub_frames
} frame_t;