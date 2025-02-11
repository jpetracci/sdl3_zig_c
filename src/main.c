#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define COLOR_WHITE 0xFFFFFFFF

int main(int argc, char *argv[])
{
    SDL_SetMainReady();
    SDL_SetAppMetadata("sdl3_test", "0.0.0", "sdl_test");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    SDL_Window *window = SDL_CreateWindow("SDL3 Test", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "render driver: %s\n", SDL_GetRendererName(renderer));

    SDL_Event event;
    bool running = true;
    SDL_FRect rect = {200, 200, 100, 100};
    while (running)
    {
        // Process events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_QUIT event\n");
                running = false;
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    SDL_DestroySurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
