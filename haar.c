/*
 * ============================================================================
 *
 *       Filename:  haar.c
 *
 *    Description:  null
 *
 *        Version:  1.0
 *        Created:  10/11/2015 05:38:37 PM
 *       Revision:  none
 *       Compiler:  clang
 *==========================================================================
 */
# include "haar.h"

long RecSum(struct Matrix mat, int x, int y, int longueur, int largeur)
{
	if(x==0 && y==0)
		return mat.arr[longueur][largeur];
	if(x==0)
		return mat.arr[longueur][largeur] - mat.arr[longueur][y-1];
	if(y==0)
		return mat.arr[longueur][largeur] - mat.arr[x-1][largeur];
	long sum = mat.arr[x-1][y-1] - mat.arr[x-1][largeur];

	return mat.arr[longueur][largeur]+sum-mat.arr[longueur][y-1];
}

long* Haar(struct Matrix mat,int x, int y)
{
	long* class = malloc(162336*sizeof(long));
	int k = 0;
	long s1,s2,s3,s4;
	for(int i=x; i<24+x;i++)
	{
		for(int j=y;j<24+y;j++)
		{
			for(int l=1;l+i<=24+x;l++)
			{
				for(int L=1;2*L+j<=24+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i,j+l,i+l-1,j+2*L-1);
					class[k] = s1-s2;
					k++;
				}
			}
		}
	}

	for(int i=x; i<24+x;i++)
	{
		for(int j=y;j<24+y;j++)
		{
			for(int l=1;l+i<=24+x;l++)
			{
				for(int L=1;3*L+j<=24+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i,j+L,i+l-1,j+2*L-1);
					s3 = RecSum(mat,i,j+2*L,i+l-1,j+3*L-1);
					class[k] = s1-s2+s3;
					k++;
				}
			}
		}
	}
	for(int i=x; i<24+x;i++)
	{
		for(int j=y;j<24+y;j++)
		{
			for(int l=1;2*l+i<=24+x;l++)
			{
				for(int L=1;L+j<=24+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i+l,j,i+2*l-1,j+L-1);
					class[k] = s1-s2;
					k++;
				}
			}
		}
	}
	for(int i=x; i<24+x;i++)
	{
		for(int j=y;j<24+y;j++)
		{
			for(int l=1;3*l+i<=24+x;l++)
			{
				for(int L=1;L+j<=24+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i+l,j,i+2*l-1,j+L-1);
					s3 = RecSum(mat,i+2*l,j,i+3*l-1,j+L-1);
					class[k] = s1-s2+s3;
					k++;
				}
			}
		}
	}
	for(int i=x; i<24+x;i++)
	{
		for(int j=y;j<24+y;j++)
		{
			for(int l=1;2*l+i<=24+x;l++)
			{
				for(int L=1;2*L+j<=24+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i+l,j,i+2*l-1,j+L-1);
					s3 = RecSum(mat,i,j+L,i+l-1,j+2*L-1);
					s4 = RecSum(mat,i+l,j+L,i+2*l-1,j+2*L-1);
					class[k] = s1-s2-s3+s4;
					k++;
				}	
			}
		}
	}
	return class;
			
}
