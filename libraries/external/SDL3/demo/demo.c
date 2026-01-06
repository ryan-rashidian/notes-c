/* SDL3 template example. */

/* Set SDL main callback macro before including SDL_main.h.
 * - SDL library will define main() after determining platform.
 * - Uses standard while loop logic for frames updates and events. */
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define SDL_INIT_FLAGS SDL_INIT_VIDEO
#define SDL_WINDOW_WIDTH 800
#define SDL_WINDOW_HEIGHT 600
#define FRAME_RATE 60
#define FRAME_TIME (1000 / FRAME_RATE)

/* Prototypes for functions used in the SDL3 main callback: */
/* SDL_AppInit is called once before anything else. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);
/* SDL_AppIterate is called over and over, possibly at refresh rate. */
SDL_AppResult SDL_AppIterate(void *appstate);
/* SDL_AppEvent is called whenever an SDL event arrives. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
/* SDL_AppQuit is called once before terminating the app. */
void SDL_AppQuit(void *appstate, SDL_AppResult result);
/* https://wiki.libsdl.org/SDL3/README-main-functions 
 * For more information, refer to the docs. */

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    /* Unused parameters. */
    (void)argc;
    (void)argv;

    /* Basic metadata about the app. */
    if (!SDL_SetAppMetadata("Example", "0.1.0", "example.x"))
        return SDL_APP_FAILURE;

    /* Initialize the SDL library. */
    if (!SDL_Init(SDL_INIT_FLAGS)) {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Allocate memory for AppState struct. */
    AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!as)
        return SDL_APP_FAILURE;
    *appstate = as;

    if (!SDL_CreateWindowAndRenderer(
        "Title",
        SDL_WINDOW_WIDTH,
        SDL_WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE,
        &as->window,
        &as->renderer
    )) return SDL_APP_FAILURE;

    SDL_SetRenderLogicalPresentation(
        as->renderer,
        SDL_WINDOW_WIDTH,
        SDL_WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *as = (AppState *)appstate;

    SDL_SetRenderDrawColor(as->renderer, 0, 127, 127, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->renderer);

    SDL_RenderPresent(as->renderer);

    SDL_Delay(FRAME_TIME);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    /* Unused parameters. */
    (void)appstate;

    /* Handle events. */
    switch (event->type) {
        case SDL_EVENT_QUIT: return SDL_APP_SUCCESS;
        default: break;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* Unused parameters. */
    (void)result;

    if (appstate != NULL) {
        AppState *as = (AppState *)appstate;
        SDL_DestroyRenderer(as->renderer);
        SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
}

