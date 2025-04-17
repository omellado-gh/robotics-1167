#include "dron.h"
#include <stdlib.h>

dron_t *create_dron(Vector3 initial_pos, Color color) {
    dron_t *dron = (dron_t *)malloc(sizeof(dron_t));

    *dron = (dron_t){
        .x = initial_pos,
        .w = 0.0,
        .uv = { 0, 0, 0 },
        .color = color
    };

    return dron;
}

void delete_dron(dron_t *dron) {
    free(dron);
}
