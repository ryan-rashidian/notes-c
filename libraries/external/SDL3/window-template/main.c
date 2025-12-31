/* Template/Demonstration for making a window with SDL3. */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "SDL Window"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
void draw_window(struct Window *window);
void run_window(struct Window *window);


int main(void)
{
    bool exit_status = EXIT_FAILURE;
    struct Window window = {0};

    if (new_window(&window)) {
        run_window(&window);
        exit_status = EXIT_SUCCESS;
    }
    free_sdl(&window);

    return exit_status;
}

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
    // Wraps init_sdl function
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
        // Identify event type
        switch (window->event.type) {
            case SDL_EVENT_QUIT:
                window->is_running = false;
                break;
            default:
                break;
        }
    }
}

void draw_window(struct Window *window)
{
    // Blue background color
    SDL_SetRenderDrawColor(window->renderer, 0, 64, 92, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
}

void run_window(struct Window *window)
{
    while (window->is_running) {
        handle_events(window);
        draw_window(window);

        SDL_Delay(16);
    }
}

