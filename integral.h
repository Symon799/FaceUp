/*
 * ============================================================================
 *
 *       Filename:  integral.h
 *
 *    Description:  null
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:38:37 PM
 *       Revision:  none
 *       Compiler:  clang
 *==========================================================================
 */

# ifndef INTEGRAL_H
# define INTEGRAL_H

# include <stdlib.h>
# include <SDL.h>
#include "pixel_operations.h"

void alloc_Mat(struct Matrix *pt_mat);
long** convertToMatrix(struct Matrix mat, SDL_Surface *surf);

#endif
