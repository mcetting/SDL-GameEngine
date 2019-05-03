#include <stdio.h>

#include <SDL.h>

// GLOBALS
const int    SCREEN_WIDTH  = 500;
const int    SCREEN_HEIGHT = 500;
const char*  APP_NAME      = "GameApp";
SDL_Window*  gWindow       = NULL;
SDL_Surface* gSurface      = NULL;
SDL_Surface* gHelloWorld   = NULL; // image to print

// function prototypes
bool init();
bool load_media();
void close();

int main(int argc, char* args[]) {
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!load_media()) {
			printf("Failed to load media!\n");
		}
		else {
			SDL_BlitSurface(gHelloWorld, NULL, gSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
		}
	}
	SDL_Delay(5000);
	close();
	return 0;
}

#pragma region FUNCTIONS
// initializes the screen and returns false if theres an error
bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// SDL_WINDOW_SHOWN - sets window to visible
		gWindow = SDL_CreateWindow(APP_NAME, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Error creating window: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// creates a framebuffer
			gSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

// loads image from bitmap into surface type
bool load_media() {
	bool success = true;
	gHelloWorld = SDL_LoadBMP("star.bmp");
	if (gHelloWorld == NULL) {
		printf("Unable to load image: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

// frees window memeory and closes sdl
void close() {
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}
#pragma endregion
#pragma region NOTES
/*
NOTES
cout is not thread safe aparently so use printf when you can
remember to set all pointers to null when deallocating them
*/
#pragma endregion