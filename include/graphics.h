#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <objects.h>
#include <raylib.h>

typedef struct _Rectangle {
    size_t width, height;
    Vector2 x;
    Vector2 *corners;
    float rotation;
} rectangle_t;

extern void draw_cube(cube_t cube);
extern void draw_cylinder(cylinder_t cylinder);
extern void draw_sphere(sphere_t sphere);

#endif