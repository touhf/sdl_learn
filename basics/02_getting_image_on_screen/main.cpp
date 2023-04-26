#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// starts up SDL and creates window
bool init();

// loads media
bool loadMedia();

// frees media and shuts down SDL
void close();

// the window we'll be rendering to
SDL_Window* gWindow = NULL;

// the surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// the image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    // initialization flag
    bool success = true;

    // initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = true;
    }
    else
    {
        // create window
        gWindow = SDL_CreateWindow("SDL Tutorial",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    // loading success flag
    bool success = true;

    // load splash image
    gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL_Error: %s\n", "./hello_world.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    // deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[])
{
    // start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            // update the surface
            SDL_UpdateWindowSurface(gWindow);

            // hack to get window stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }
    // free resources and close SDL
    close();

    return 0;
}
