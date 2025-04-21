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

extern void draw_rectangle(Color *screen, rectangle_t rec, Color color);
extern void draw_background(Color *screen, Color color);
