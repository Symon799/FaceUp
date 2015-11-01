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
long** convertToMatrix(struct Matrix *pt_mat, SDL_Surface *surf);
SDL_Surface* convertToImage(struct Matrix *pt_mat, SDL_Surface *intImg);
void haar_test(struct Matrix mat);
long RecSum(struct Matrix mat, int x, int y, int longueur, int largeur);
long *Haar(struct Matrix mat,int x,int y);

# endif
