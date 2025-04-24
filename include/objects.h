#include <raylib.h>

typedef struct _Object {
    Vector3 position;
    Vector3 rotation;
    Model model;
    Color color;
} object_t;

typedef struct _Cube {
    object_t object;
    Vector3 size;
} cube_t;

typedef struct _Sphere {
    object_t object;
    float radius;
    void *padding_;
} sphere_t;

typedef struct _Cylinder {
    object_t object;
    float radius;
    float height;
    void *padding_;
} cylinder_t;

extern cube_t *create_cube(Vector3 size, Vector3 position, Vector3 rotation, Color color);
extern sphere_t *create_sphere(float radius, Vector3 position, Vector3 rotation, Color color);
extern cylinder_t *create_cylinder(float radius, float height, Vector3 position, Vector3 rotation, Color color);

extern void destroy_cube(cube_t *cube);
extern void destroy_sphere(sphere_t *sphere);
extern void destroy_cylinder(cylinder_t *cylinder);