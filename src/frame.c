#include <frame.h>
#include <graphics.h>

#include <raymath.h>
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

void draw_frame(frame_t *frame) {
    void **entities = get_array(frame->entities);

    float y_rotation = frame->rotation.y;

    for (size_t i = 0; i < frame->entities->size; i++) {
        cube_t entity = *(cube_t *)entities[i];

        entity.object.position = Vector3RotateByAxisAngle(entity.object.position, (Vector3){0.0f, 1.0f, 0.0f}, y_rotation);
        entity.object.position = Vector3Add(entity.object.position, frame->position);

        Matrix t_rotation = MatrixRotate((Vector3){0.0f, 1.0f, 0.0f}, y_rotation + entity.object.rotation.y);
        entity.object.model.transform = MatrixMultiply(t_rotation, entity.object.model.transform);

        draw_cube(entity);
    }

    free(entities);
}

void add_entity(frame_t *frame, void *entity) {

    if (frame == NULL || entity == NULL) {
        return;
    }

    append(frame->entities, entity);
}

void destroy_frame(frame_t *frame) {
    if (frame == NULL) {
        return;
    }
    destroy_linked_list(frame->entities);

    free(frame);
}