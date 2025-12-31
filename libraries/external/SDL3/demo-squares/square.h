#ifndef SQUARE_H
#define SQUARE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
    float x, y, z;
    float sx, sy;
    uint8_t r, g, b;
} Vec3d;

void init_squares(void);
void project(Vec3d p, float *sx, float *sy);
Uint64 draw_square(struct Window *window, Uint64 now, Uint64 last);

#endif

