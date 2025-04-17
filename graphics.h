#include <stdio.h>
#include <raylib.h>

typedef struct _Rectangle {
    size_t width, height;
    Vector2 x;
    Vector2 *corners;
    float rotation;
} rectangle_t;

extern void draw_rectangle(Color *screen, rectangle_t rec, Color color);
extern void draw_background(Color *screen, Color color);
