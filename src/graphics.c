#include <graphics.h>
#include <config.h>

#include <raymath.h>

void draw_object(object_t object) {
    object.model.transform = MatrixMultiply(MatrixRotateXYZ(object.rotation), object.model.transform);
    DrawModel(object.model, object.position, 1.0f, object.color);
}

void draw_cube(cube_t cube) {
    draw_object(cube.object);
}

void draw_cylinder(cylinder_t cylinder) {
    draw_object(cylinder.object);
}

void draw_sphere(sphere_t sphere) {
    draw_object(sphere.object);
}