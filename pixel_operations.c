
/* ============================================================================
 *
 *       Filename:  pixel_operations.c
 *
 *    Description:  GreyLevel
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:39:03 PM
 *       Revision:  none
 *       Compiler:  clang
 *
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
	Uint8 r, g, b, val;
	Uint32 pixel;
	for (int i = 0; i < surf->h; i++)
	{
		for (int j = 0; j < surf->w; j++)
		{
			//Uint8 r, g, b;

			pixel = getpixel(surf, j, i);

			SDL_GetRGB(pixel, surf->format, &r, &g, &b);

			r = (Uint8)((float)r * 0.3);
			g = (Uint8)((float)g * 0.59);
			b = (Uint8)((float)b * 0.11);

			val = r + g + b;

			pixel = SDL_MapRGB(surf->format, val, val, val);

			putpixel(surf, j, i, pixel);
		}
	}
}

void displaySquare(SDL_Surface *surf, int x, int y, int len)
{
	Uint32 pixel;
	int j = x;
	for (int i = y; i <= y + len; i++)
	{
		pixel = SDL_MapRGB(surf->format, 0, 254, 0);
		putpixel(surf, y, j, pixel);
		putpixel(surf, i, x, pixel);
		putpixel(surf, y + len, j, pixel);
		putpixel(surf, i, x + len, pixel);
		j++;	
	}
}
