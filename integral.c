/*
 * ============================================================================
 *
 *       Filename:  integral.c
 *
 *    Description:  null
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:38:37 PM
 *       Revision:  none
 *       Compiler:  clang
 *==========================================================================
 */

# include "integral.h"

void alloc_Mat(struct Matrix *pt_mat)
{
	struct Matrix mat = *pt_mat;

	pt_mat->arr = malloc((mat.x)*sizeof(long*));

	for ( long i = 0; i < (mat.x); i++)
		mat.arr[i] = calloc((mat.y),sizeof(long));
}

long** convertToMatrix(struct Matrix *pt_mat, SDL_Surface *surf)
{
	struct Matrix mat = *pt_mat;

	alloc_Mat(pt_mat);

	//test : Affichage de la Matrice d'origine
	/*for(int i = 0; i < mat.x; i++)
	{
		for(int j = 0; j < mat.y; j++)
			printf("%d ", getpixel(surf,j,i) % 255);

		printf("\n");
	}*/

	for (int x = mat.x-1; x >= 0; x--)
	{
		for (int y = 0; y < mat.y; y++)
		{	
			mat.arr[x][y] = (long)(getpixel(surf,y,x) % 255);

				for (int lgn =0; lgn < x; lgn++)
					mat.arr[x][y] += (long)(getpixel(surf,y,lgn) % 255);

			if (y > 0)
				mat.arr[x][y] += mat.arr[x][y-1];
		}
	}
	//test : affichage de matrix
	/*printf("\n\n");
	for(int i = 0; i < mat.x; i++)
	{
		for(int j = 0; j < mat.y; j++)
			printf("%ld ", mat.arr[i][j]);
		printf("\n");
	}*/
	
	return mat.arr;
}
