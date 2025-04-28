#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define GRAVITY 9.8f

#define WORLD_WIDTH 24
#define WORLD_HEIGHT 32
#define CANCHA_WIDTH 9.8f
#define CANCHA_HEIGHT 17.8f

#define POS_RING_RED  ((Vector3){  8.74f, 1.3f, 0.0f })
#define POS_RING_BLUE ((Vector3){ -8.74f, 1.3f, 0.0f })

#define N_ROBOTS_PER_TEAM 1

#define ONCE_TEAM 1

#define WAIT_TIME_FOR_SHOT 0.5f

#define BACKGROUND_COLOR WHITE

#endif