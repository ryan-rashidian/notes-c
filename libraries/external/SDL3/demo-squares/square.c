#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "window.h"
#include "config.h"

typedef struct {
    float x, y, z;
    float sx, sy;
    uint8_t r, g, b;
} Vec3d;

const float starting_x[] = { 50.0f,  00.0f, -50.0f, -50.0f};
const float starting_y[] = { 50.0f, -50.0f,  50.0f, -00.0f};
const float starting_z[] = {300.0f, 235.0f, 170.0f, 105.0f};
const uint8_t colors[NUM_SQUARES][3] = {
    {255,   0,   0},
    {  0, 255,   0},
    {  0,   0, 255},
    {120,   0, 120}
};
float angle = 0.0f;
Vec3d squares[NUM_SQUARES];

int compare_vec(const void *p1, const void *p2);
void init_squares(void);
void rotate(Vec3d *p, float angle);
void project(Vec3d p, float *sx, float *sy);
void update_square_pos(float delta);
Uint64 draw_square(struct Window *window, Uint64 now, Uint64 last);

int compare_vec(const void *p1, const void *p2) {
    // Explicit cast: valid in C++
    // const Vec3d *z1 = (const Vec3d *)p1;
    // const Vec3d *z2 = (const Vec3d *)p2;

    // Implicit conversion: only in C
    const Vec3d *z1 = p1;
    const Vec3d *z2 = p2;

    if (z1->z < z2->z) return  1;
    if (z1->z > z2->z) return -1;
    return 0;
}

void init_squares(void)
{
    for (int i = 0; i < NUM_SQUARES; i++) {
        squares[i].x  = starting_x[i];
        squares[i].y  = starting_y[i];
        squares[i].z  = starting_z[i];
        squares[i].r  = colors[i][0];
        squares[i].g  = colors[i][1];
        squares[i].b  = colors[i][2];
    }
}

void rotate(Vec3d *p, float angle)
{
    // Rotate the point around the origin (0, 0) by 'angle' radians.
    // 2D rotation formula:
    // x1 = x * cos(angle) - y * sin(angle)
    // y1 = x * sin(angle) + y * cos(angle)
    // Creates a circular/orbit-like motion as 'angle' changes over time.
    float c = cosf(angle);
    float s = sinf(angle);

    float x = p->x * c - p->y * s;
    float y = p->x * s - p->y * c;

    p->x = x;
    p->y = y;
}

void project(Vec3d p, float *sx, float *sy)
{
    // Projective perspective formula:
    // Calculates how far from the center each point is.
    // Points farther away (larger z) appear closer to the center.
    // x1 = x/z
    // y1 = y/z
    // Multiply by FOCAL_LENGTH to scale results into pixel coordinates
    // Screen coordinate origin is at the top left corner (0, 0),
    // adding WINDOW_WIDTH/2 and WINDOW_HEIGH/2 moves it to the center.
    *sx = (p.x/ p.z) * FOCAL_LENGTH + WINDOW_WIDTH / 2.0f;
    *sy = (p.y/ p.z) * FOCAL_LENGTH + WINDOW_HEIGHT / 2.0f;
}

void update_square_pos(float delta)
{
    for (int i = 0; i < NUM_SQUARES; i++) {
        // Move along the z-axis
        squares[i].z -= Z_SPEED * delta;
        if (squares[i].z < 40.0f) {
            squares[i].z = 300.0f;
        }

        angle += 1.5f * delta;
        Vec3d rotated = squares[i];
        rotate(&rotated, angle);
        project(rotated, &squares[i].sx, &squares[i].sy);
    }
}

Uint64 draw_square(struct Window *window, Uint64 now, Uint64 last)
{
    float delta = (now - last) / 1000.0f;
    last = now;

    update_square_pos(delta);

    // Sort by z-axis distance before rendering
    qsort(squares, NUM_SQUARES, sizeof(Vec3d), compare_vec);

    for (int i = 0; i < NUM_SQUARES; i++) {
        SDL_FRect square = {
            .x = squares[i].sx - SQUARE_SIZE / 2.0f,
            .y = squares[i].sy - SQUARE_SIZE / 2.0f,
            .w = SQUARE_SIZE * (FOCAL_LENGTH / squares[i].z),
            .h = SQUARE_SIZE * (FOCAL_LENGTH / squares[i].z)
        };

        // Render square
        SDL_SetRenderDrawColor(
            window->renderer,
            squares[i].r,
            squares[i].g,
            squares[i].b,
            255
        );
        SDL_RenderFillRect(window->renderer, &square);
    }

    return last;
}

