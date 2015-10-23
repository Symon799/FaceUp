/*
 * ============================================================================
 *
 *       Filename:  pixel_operations.h
 *
 *    Description:  null
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:38:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Symon
 *
 * ============================================================================
 */

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>

struct Matrix
{
    int x;
    int y;
	long **arr;
};

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void convertGreyLevel(SDL_Surface *surf);
long** convertToMatrix(struct Matrix *pt_mat, SDL_Surface *surf);
SDL_Surface* convertToImage(struct Matrix *pt_mat, SDL_Surface *intImg);
void haar_test(struct Matrix mat);

# endif
