#include <raylib.h>

typedef struct _Object {
    Vector3 position;
    Vector3 rotation;
    Model model;
    Color color;
} object_t;

typedef struct _Cube {
    Vector3 size;
    object_t object;
} cube_t;

typedef struct _Sphere {
    float radius;
    object_t object;
} sphere_t;

typedef struct _Cylinder {
    float radius;
    float height;
    object_t object;
} cylinder_t;

extern cube_t *create_cube(Vector3 size, Vector3 position, Vector3 rotation, Color color);
extern sphere_t *create_sphere(float radius, Vector3 position, Vector3 rotation, Color color);
extern cylinder_t *create_cylinder(float radius, float height, Vector3 position, Vector3 rotation, Color color);

extern void destroy_cube(cube_t *cube);
extern void destroy_sphere(sphere_t *sphere);
extern void destroy_cylinder(cylinder_t *cylinder);