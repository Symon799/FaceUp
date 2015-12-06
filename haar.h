/*
 * ============================================================================
 *
 *       Filename:  haar.h
 *
 *    Description:  null
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:38:37 PM
 *       Revision:  none
 *       Compiler:  clang
 *==========================================================================
 */

# include <stdlib.h>
# include <SDL.h>
#include "pixel_operations.h"

typedef struct {
	long Haar;
	int posx,posy,longueur,largeur,type;

} feat;

long RecSum(struct Matrix mat, int x, int y, int longueur, int largeur);
feat *Haar(struct Matrix mat,int x,int y,int longueur);






