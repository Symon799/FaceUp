/*
 * ============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  watashi wa purojectu desu
 *
 *        Version:  1.0
 *        Created:  10/10/2015 11:53:44 PM
 *       Revision:  none
 *       Compiler:  clang
 *
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

#include "pixel_operations.h"
#include "haar.h"
#include "integral.h"

void init_sdl(void) 
{
	// Init only the video part
	if(SDL_Init(SDL_INIT_VIDEO) == -1) 
	{
		// If it fails, die with an error message
		errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
	}
}

SDL_Surface* load_image(char *path) 
{
	SDL_Surface *img;
	// Load an image using SDL_image with format detection
	img = IMG_Load(path);
	if (!img)
		// If it fails, die with an error message
		errx(3, "can't load %s: %s", path, IMG_GetError());
	return img;
}

void wait_for_keypressed(void)
{
	SDL_Event event;
	for (;;) 
	{
		// Take an event
		SDL_PollEvent( &event );
		// Switch on event type
		switch (event.type)
		{
			// Someone pressed a key -> leave the function
			case SDL_KEYDOWN: return;
			default: break;
		}
	}
}

SDL_Surface* display_image(SDL_Surface *img) 
{
	SDL_Surface *screen;
	// Set the window to the same size as the image
	screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
	
	if ( screen == NULL ) 
	{
		// error management
		errx(1, "Couldn't set %dx%d video mode: %s\n",
				img->w, img->h, SDL_GetError());
	}

	/*  Blit onto the screen surface */
	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		warnx("BlitSurface error: %s\n", SDL_GetError());

	// Update the screen
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

	// wait for a key
	wait_for_keypressed();

	// return the screen for further uses
	return screen;
}


int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(2, "Usage:\n%s <image>", argv[0]);

	init_sdl();
	SDL_Surface *image = load_image(argv[1]);

	display_image(image);
	convertGreyLevel(image);
	
	struct Matrix myMatrix;


	myMatrix.x = image->h;
	myMatrix.y = image->w;
	
	display_image(image);
	myMatrix.arr = convertToMatrix(&myMatrix, image);

	printf("%ld\n", Haar(myMatrix,0,0)[0]);
	printf("%ld\n",  (2*myMatrix.arr[0][0] - myMatrix.arr[0][1]));

	//SDL_FreeSurface(image);

	return 0;
}
