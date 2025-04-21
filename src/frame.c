#include <frame.h>

#include <stdlib.h>

frame_t *create_frame(Vector3 position, Vector3 rotation) {
    frame_t *frame = (frame_t *)malloc(sizeof(frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->position = position;
    frame->rotation = rotation;
    frame->entities = create_linked_list();

    return frame;
}

void add_entity(frame_t *frame, void *entity, bool is_model) {

    if (frame == NULL || entity == NULL) {
        return;
    }

    append(frame->entities, entity, is_model);
}

void destroy_frame(frame_t *frame) {
    if (frame == NULL) {
        return;
    }
    destroy_linked_list(frame->entities);

    free(frame);
}