#include <frame.h>

#include <raylib.h>
#include <stdio.h>

typedef struct RobotUniciclo {
    frame_t *obj;
    float d;
    float w;
    Vector2 v, uv;
    size_t steps;
    Color team;
} uniciclo_t;

extern uniciclo_t* create_robot(Vector3 pos, float d, Color team);
extern void delete_robot(uniciclo_t* robot);
extern void move_robot(uniciclo_t* robot);
