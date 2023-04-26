// using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

// screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // the window we'll be rendering to
    SDL_Window* window = NULL;

    // the surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // create window
        window = SDL_CreateWindow("SDL Tutorial", 
                                    SDL_WINDOWPOS_UNDEFINED, // x position of window
                                    SDL_WINDOWPOS_UNDEFINED, // y position of window
                                    SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // fill the surface white
            SDL_FillRect(screenSurface, 
                        NULL, 
                        SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
            
            // update the surface
            SDL_UpdateWindowSurface(window);

            // hack to get window to stay up
            SDL_Event e; 
            bool quit = false; 
            while( quit == false ){ 
                while( SDL_PollEvent( &e ) ) { 
                    if( e.type == SDL_QUIT ) quit = true; 
                } 
            }
       }
    }
    // destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
