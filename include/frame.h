#ifndef FRAME_H
#define FRAME_H

#include <linked_list.h>

#include <raylib.h>
#include <stdio.h>

typedef struct Frame {
    Vector3 position;
    Vector3 rotation;
    linked_list_t *entities;
} frame_t;

extern frame_t *create_frame(Vector3 position, Vector3 rotation);
extern void add_entity(frame_t *frame, void *entity);
extern void destroy_frame(frame_t *frame);
extern void draw_frame(frame_t *frame);

#endif