#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "square.h"
#include "config.h"

#define SDL_FLAGS SDL_INIT_VIDEO
#define FRAME_TIME (1000 / FRAME_RATE)

bool init_sdl(struct Window *window);
bool new_window(struct Window *window);
void free_sdl(struct Window *window);
void handle_events(struct Window *window);
Uint64 draw_window(struct Window *window, Uint64 now, Uint64 last);
void run_window(struct Window *window);

bool init_sdl(struct Window *window)
{
    if (!SDL_Init(SDL_FLAGS)) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    window->window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window->window) {
        printf("Error creating window: %s\n", SDL_GetError());
        return false;
    }
    window->renderer = SDL_CreateRenderer(window->window, NULL);
    if (!window->renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool new_window(struct Window *window)
{
    if (!init_sdl(window))
        return false;

    window->is_running = true;
    return true;
}

void free_sdl(struct Window *window)
{
    if (window->renderer) {
        SDL_DestroyRenderer(window->renderer);
        window->renderer = NULL;
    }
    if (window->window) {
        SDL_DestroyWindow(window->window);
        window->window = NULL;
    }

    SDL_Quit();
}

void handle_events(struct Window *window)
{
    while (SDL_PollEvent(&window->event)) {
        switch (window->event.type) {
            case SDL_EVENT_QUIT:
                window->is_running = false;
                break;
            default:
                break;
        }
    }
}

Uint64 draw_window(struct Window *window, Uint64 now, Uint64 last)
{
    SDL_SetRenderDrawColor(window->renderer, 0, 64, 92, 255);
    SDL_RenderClear(window->renderer);

    Uint64 update_last = draw_square(window, now, last);

    SDL_RenderPresent(window->renderer);

    return update_last;
}

void run_window(struct Window *window)
{
    Uint64 frame_last = SDL_GetTicks();
    init_squares();

    while (window->is_running) {
        Uint64 frame_start = SDL_GetTicks();

        handle_events(window);
        frame_last = draw_window(window, frame_start, frame_last);

        Uint64 frame_end = SDL_GetTicks();
        int frame_duration = frame_end - frame_start;
        int delay = FRAME_TIME - frame_duration;
        if (delay > 0)
            SDL_Delay(delay);
    }
}

