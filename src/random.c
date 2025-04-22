#include <random.h>

#include <stdlib.h>

float get_random_float(float min, float max) {
    return ((float)rand() / (float)(RAND_MAX)) * (max - min) + min;
}

size_t get_random_size_t(size_t min, size_t max) {
    return (size_t)(get_random_float((float)min, (float)max));
}