#include "objects.h"
#include <stdlib.h>

object_t create_object(Vector3 position, Vector3 rotation, Color color) {
    object_t object = { 0 };

    object.position = position;
    object.rotation = rotation;
    object.color = color;

    return object;
}

void destroy_object(object_t *object) {
    UnloadModel(object->model);
}

cube_t *create_cube(Vector3 size, Vector3 position, Vector3 rotation, Color color) {
    cube_t *cube = (cube_t *)malloc(sizeof(cube_t));

    cube->size = size;
    cube->object = create_object(position, rotation, color);

    cube->object.model = LoadModelFromMesh(GenMeshCube(size.x, size.y, size.z));

    return cube;
}

sphere_t *create_sphere(float radius, Vector3 position, Vector3 rotation, Color color) {
    sphere_t *sphere = (sphere_t *)malloc(sizeof(sphere_t));

    sphere->radius = radius;
    sphere->object = create_object(position, rotation, color);

    sphere->object.model = LoadModelFromMesh(GenMeshSphere(radius, 32, 32));

    return sphere;
}

cylinder_t *create_cylinder(float radius, float height, Vector3 position, Vector3 rotation, Color color) {
    cylinder_t *cylinder = (cylinder_t *)malloc(sizeof(cylinder_t));

    cylinder->radius = radius;
    cylinder->height = height;
    cylinder->object = create_object(position, rotation, color);

    cylinder->object.model = LoadModelFromMesh(GenMeshCylinder(radius, height, 32));

    return cylinder;
}

void destroy_cube(cube_t *cube) {
    destroy_object(&cube->object);
    free(cube);
}

void destroy_sphere(sphere_t *sphere) {
    destroy_object(&sphere->object);
    free(sphere);
}

void destroy_cylinder(cylinder_t *cylinder) {
    destroy_object(&cylinder->object);
    free(cylinder);
}