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
	Uint8 r, g, b, val;
	Uint32 pixel;
	for (int i = 0; i < surf->w; i++)
	{
		for (int j = 0; j < surf->h; j++)
		{
			//Uint8 r, g, b;

			pixel = getpixel(surf, i, j);

			SDL_GetRGB(pixel, surf->format, &r, &g, &b);

			r = (Uint8)((float)r * 0.3);
			g = (Uint8)((float)g * 0.59);
			b = (Uint8)((float)b * 0.11);

			val = r + g + b;

			pixel = SDL_MapRGB(surf->format, val, val, val);

			putpixel(surf, i, j, pixel);
		}
	}
}


void alloc_Mat(struct Matrix *pt_mat)
{
	struct Matrix mat = *pt_mat;

	pt_mat->arr = (long**)malloc((mat.x)*sizeof(long*));
	for ( long i = 0; i < (mat.x); i++ )
	{
		mat.arr[i] = (long*)malloc((mat.y)*sizeof(long));
	}
}

SDL_Surface* convertToImage(struct Matrix *pt_mat, SDL_Surface *intImg)
{
	Uint8 val;
	Uint32 pixel;
	
	struct Matrix mat = *pt_mat;

	for (int j = 0; j < mat.y; j++)
	{
		for (int i = 0; i < mat.x; i++)
		{
			val = (Uint8)(mat.arr[i][j]);
			printf ("i: %d and j: %d and val: %d\n", i, j, val);

			pixel =  SDL_MapRGB(intImg->format, val, val, val);
			putpixel(intImg, i, j, pixel);	
		}
	}
	return intImg;
}

long** convertToMatrix(struct Matrix *pt_mat, SDL_Surface *surf)
{
	struct Matrix mat = *pt_mat;

	alloc_Mat(pt_mat);

	//test : Affichage de la Matrice d'origine
	for (int j = 0; j<mat.y; j++)
	{
		for (int i = 0; i < (mat.x); i++)
		{		
			printf ("%ld ", (long)(getpixel(surf,i,j) % 255));
		}
		printf("\n");
	}

	for (int y = mat.y; y >= 0; y--)
	{
		//printf ("mat.x: %d\n", mat.x);
		for (int x = 0; x < mat.x; x++)
		{	
			mat.arr[x][y] = (long)(getpixel(surf,x,y) % 255);

				for (int lgn =0; lgn < y; lgn++)
				{
					mat.arr[x][y] += (long)(getpixel(surf,x,lgn) % 255);
					//printf ("lgn: %d and y: %d and x: %d \n", lgn, y, x);
				}

			if (x > 0)
				mat.arr[x][y] += mat.arr[x-1][y];
			//printf("sum: %ld ", sum);
		}
	}
	//test : affichage de matrix
	printf("\n\n");
	for (int j = 0; j < (mat.y); j++)
	{
		for (int i = 0; i < (mat.x); i++)
		{
			printf("%ld ", mat.arr[i][j]);				
		}
		printf("\n");
	}
	printf("\n");
	return mat.arr;
}

void haar_test(struct Matrix mat)
{
	long s1, s2;
	int k = 0;
	long class[mat.x*mat.y];
	for (int j = 0; j < mat.y; j++)
	{
		for (int i = 0; i < mat.x; i++)
		{
			if (i+23 <= mat.x && j+23 <= mat.y)
			{
				s1 = mat.arr[i+12][j+23];
				s2 = mat.arr[i+23][j+23] - s1;
				class[k] = s1 -s2;
				k++;
			}
		}
	}
}

long RecSum(struct Matrix mat, int x, int y, int longueur, int largeur)
{
	if(x==0 && y==0)
		return mat.arr[longueur][largeur];
	if(x==0)
		return mat.arr[longueur][largeur] - mat.arr[longueur][y-1];
	if(y==0)
		return mat.arr[longueur][largeur] - mat.arr[x-1][largeur];

	return mat.arr[longueur][largeur]+mat.arr[x-1][y-1]-mat.arr[x-1][largeur]-mat.arr[longueur][y-1];
}

