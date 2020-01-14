// use SDL2 and standard input/output
#include <SDL.h>
#include <stdio.h>

// windows dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//// Declared functions
// starts SDL and creates window
bool init();
// loads media
bool loadMedia();
// frees media and shuts down SDL
void close();

//// Global Variables
// main game window
SDL_Window* gWindow = NULL;
// game window's surface
SDL_Surface* gScreenSurface = NULL;
// image to be loaded
SDL_Surface* gHelloWorld = NULL;


// main function
int main(int argc, char* args[])
{
	

	return 0;
}