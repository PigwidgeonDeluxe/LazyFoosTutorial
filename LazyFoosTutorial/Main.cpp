// use SDL2 and standard input/output
#include <SDL.h>
#include <stdio.h>

// windows dimensions
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

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
	// Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{
				// main loop flag
				bool quit = false;

				// event handler
				SDL_Event e;

				while (!quit) // as long as we are running the application
				{
					// handle events on the queue until empty
					while (SDL_PollEvent(&e) != 0)
					{
						// user requests to quit
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
					}


					//Apply the image
					SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

					//Update the surface
					SDL_UpdateWindowSurface(gWindow);
				}
			}
		}

		//Free resources and close SDL
		close();

		return 0;
}

// initialization function
bool init()
{
	//init flag
	bool success = true;

	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// creat window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window not created. SDL_Error: %s\n", SDL_GetError());
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

// function to load our image
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	char filePath[] = "tut_2/image.bmp";

	//Load splash image
	gHelloWorld = SDL_LoadBMP(filePath);
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath, SDL_GetError());
		success = false;
	}

	return success;
}

// function to close the window
void close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}