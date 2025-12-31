/* Demonstration of SDL3 with animated squares. */

#include <stdlib.h>
#include "window.h"


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

