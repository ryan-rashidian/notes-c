#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>

struct Window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool is_running;
};

bool init_sdl(struct Window *window);
bool new_window(struct Window *window);
void free_sdl(struct Window *window);
void handle_events(struct Window *window);
Uint64 draw_window(struct Window *window, Uint64 now, Uint64 last);
void run_window(struct Window *window);

#endif

