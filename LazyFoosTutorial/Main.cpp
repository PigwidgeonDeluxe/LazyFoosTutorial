// use SDL2 and standard input/output
#include <SDL.h>
#include <stdio.h>
#include <string>

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
// current image being displayed
SDL_Surface* gCurrentSurface = NULL;
// function for loading an individual image
SDL_Surface* loadSurface(std::string path);



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

					// apply the image stretched
					SDL_Rect stretchRect;
					stretchRect.x = 0;
					stretchRect.y = 0;
					stretchRect.w = SCREEN_WIDTH;
					stretchRect.h = SCREEN_HEIGHT;
					SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

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
	// loading success flag
	bool success = true;

	// load stretching surface
	gCurrentSurface = loadSurface("tut_5/stretch.bmp");
	if (gCurrentSurface == NULL)
	{
		printf("Failed to load stretching image.\n");
		success = false;
	}

	return success;
}

// function to close the window
void close()
{

	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;


	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

// function for loading individual images
SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}