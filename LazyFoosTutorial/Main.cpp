// use SDL2 and standard input/output
#include <SDL.h>
#include <stdio.h>
#include <string>

// windows dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// key press constants for surfaces (automatically enumerated from 0 to 5)
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

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
// images that correspont to keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
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

				// display initial default surface
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
						// user key input
						else if (e.type == SDL_KEYDOWN)
						{
							// Select surfaces based on key press
							switch (e.key.keysym.sym)
							{
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;

							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;

							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;

							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;

							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
							}
						}
					}


					//Apply the image
					SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

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

	// load default screen/surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("tut_4/press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	// load up screen/surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("tut_4/up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	// load down screen/surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("tut_4/down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	// load left screen/surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("tut_4/left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	// load right screen/surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("tut_4/right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	return success;
}

// function to close the window
void close()
{
	// deallocate all surfaces
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

// function for loading individual images
SDL_Surface* loadSurface(std::string path)
{
	// load an image at a given location
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s . SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}