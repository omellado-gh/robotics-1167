#include <linked_list.h>

#include <raylib.h>
#include <stdio.h>

// a simple visual python frame implementation
typedef struct Frame {
    Vector3 position;  // 3D coordinates
    Vector3 rotation; // angle in radians
    linked_list_t *entities; // list of models or sub_frames
} frame_t;

extern frame_t *create_frame(Vector3 position, Vector3 rotation);
extern void add_entity(frame_t *frame, void *entity, bool is_model);
extern void destroy_frame(frame_t *frame);