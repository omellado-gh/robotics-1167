#include "frame.h"

#include <stdlib.h>

frame_t *create_frame(Vector3 v, float phi) {
    frame_t *frame = (frame_t *)malloc(sizeof(frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->position = v;
    frame->rotation = phi;
    frame->entities = create_linked_list();

    return frame;
}

int add_sub_frame(frame_t *frame, frame_t *sub_frame) {



    return 0;
}

void destroy_frame(frame_t *frame) {
    if (frame == NULL) {
        return;
    }
    destroy_linked_list(frame->entities);

    free(frame);
}