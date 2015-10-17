/*
 * ============================================================================
 *
 *       Filename:  pixel_operations.c
 *
 *    Description:  GreyLevel & IntegralImage
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:39:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Symon
 *
 *
 * ============================================================================
 */

 
# include "pixel_operations.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
	int bpp = surf->format->BytesPerPixel;
	return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
	Uint8 *p = pixelref(surface, x, y);
	switch(surface->format->BytesPerPixel) {
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
		case 4:
			return *(Uint32 *)p;
	}
	return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
	Uint8 *p = pixelref(surface, x, y);
	switch(surface->format->BytesPerPixel) {
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

void convertGreyLevel(SDL_Surface *surf)
{
	for (int i = 0; i < surf->w; i++)
	{
		for (int j = 0; j < surf->h; j++)
		{
			Uint8 r, g, b;

			Uint32 pixel = getpixel(surf, i, j);

			SDL_GetRGB(pixel, surf->format, &r, &g, &b);

			r = (Uint8)((float)r * 0.3);
			g = (Uint8)((float)g * 0.59);
			b = (Uint8)((float)b * 0.11);

			Uint8 val = r + g + b;

			pixel = SDL_MapRGB(surf->format, val, val, val);

			putpixel(surf, i, j, pixel);
		}
	}
}

void allocMatrix1(Matrix mat)
{
	mat.arr = (long**)malloc((mat.y+1) * sizeof(long*));

	for(int i = 0; i < (mat.y+1); i++)
		  mat.arr[i] = (long*)malloc((mat.x+1) * sizeof(long));
}

void allocMatrix(Matrix mat) 
{
	mat.arr = (long**)malloc((mat.x+1)*sizeof(long*));
	for ( long i = 0; i < (mat.x+1); i++ )
	{
		mat.arr[i] = (long*)malloc((mat.y+1)*sizeof(long));
	}
	mat.arr[2][3] = 0;
}

void convertToMatrix(Matrix mat, SDL_Surface *surf)
{

	mat.arr = (long**)malloc((mat.y+1)*sizeof(long*));
	for ( long i = 0; i < (mat.y+1); i++ )
	{
		mat.arr[i] = (long*)malloc((mat.x+1)*sizeof(long));
	}


	for (int i = 0; i < (mat.y+1); i++)
	{
		for (int j = 0; j < (mat.x+1); j++)
		{
			if (i == 0 || j == 0)
				mat.arr[i][j] = 0;
			else if (i == 1 && j== 1)
				mat.arr[1][1] = (long)(getpixel(surf, 0, 0));
			else if (i >= 2 && j >=2)
				mat.arr[i][j] = (long)(getpixel(surf, i-1, j-1) + getpixel(surf, i-2, j-1) + getpixel(surf, i-1, j-2) - getpixel(surf, i-2, j-2));
			else if (i < 2 && j < 2)
				mat.arr[i][j] = (long)(getpixel(surf, i-1, j-1));
			else if (i < 2)
				mat.arr[i][j] = (long)(getpixel(surf, i-1, j-1) + getpixel(surf, i-1, j-2));
			else
				mat.arr[i][j] = (long)(getpixel(surf, i-1, j-1) + getpixel(surf, i-2, j-1));

			//printf ("%ld ", mat.arr[i][j]);
		}
		//printf("\n");
	}
}
