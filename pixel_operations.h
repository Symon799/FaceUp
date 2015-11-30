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
 *       Compiler:  clang
 *==========================================================================
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

Uint32 getpixel(SDL_Surface *surface, unsigned y, unsigned x);
void putpixel(SDL_Surface *surface, unsigned y, unsigned x, Uint32 pixel);
void convertGreyLevel(SDL_Surface *surf);
void displaySquare(SDL_Surface *surf, int x, int y, int len);

# endif
