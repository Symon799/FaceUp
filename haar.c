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
# include <math.h>

int min(int a, int b){return a<b? a : b;}

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

/*cls* features(struct Matrix mat)
{
	for(int longueur = 24; longueur<=min(mat.x,mat.y);longueur++)
	{
		for (int x = 0; x<=Mat.x-longueur;x++)
		{
			for(int y = 0; y<Mat.y-longueur;y++)
				Haar(mat, x,y,longueur);
		}
	}
}*/

long* Haar(struct Matrix mat,int x, int y,int longueur)
{
	long* class = malloc(162336*sizeof(long));
	int k = 0;
	long s1,s2,s3,s4;
	for(int i=x; i<longueur+x;i++)
	{
		for(int j=y;j<longueur+y;j++)
		{
			for(int l=1;l+i<=longueur+x;l++)
			{
				for(int L=1;2*L+j<=longueur+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i,j+l,i+l-1,j+2*L-1);
					class[k] = s1-s2;
					k++;
				}
			}
		}
	}

	for(int i=x; i<longueur+x;i++)
	{
		for(int j=y;j<longueur+y;j++)
		{
			for(int l=1;l+i<=longueur+x;l++)
			{
				for(int L=1;3*L+j<=longueur+y;L++)
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
	for(int i=x; i<longueur+x;i++)
	{
		for(int j=y;j<longueur+y;j++)
		{
			for(int l=1;2*l+i<=longueur+x;l++)
			{
				for(int L=1;L+j<=longueur+y;L++)
				{
					s1 = RecSum(mat,i,j,i+l-1,j+L-1);
					s2 = RecSum(mat,i+l,j,i+2*l-1,j+L-1);
					class[k] = s1-s2;
					k++;
				}
			}
		}
	}
	for(int i=x; i<longueur+x;i++)
	{
		for(int j=y;j<longueur+y;j++)
		{
			for(int l=1;3*l+i<=longueur+x;l++)
			{
				for(int L=1;L+j<=longueur+y;L++)
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
	for(int i=x; i<longueur+x;i++)
	{
		for(int j=y;j<longueur+y;j++)
		{
			for(int l=1;2*l+i<=longueur+x;l++)
			{
				for(int L=1;2*L+j<=longueur+y;L++)
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

int hwef(long haar) {return haar<0 ? -1 : (haar!=0);}

long Adaboost(struct Matrix mat,/*SDL_Surface **pos_tab, SDL_Surface **neg_tab,*/int nbpos, int nbneg, int T)
{
	float* alpha = malloc(T*sizeof(float));
	int wp = 0,wn = 0,wz = 0;
	int *h = malloc (T*sizeof(int));
	float *w = malloc((nbpos+nbneg)*sizeof(float));
	long *haar = Haar(mat,0,0,24);
	float Z;
	for (int i = 0;i<nbpos+nbneg;i++)
		w[i] = 1/(nbpos+nbneg);
	for (int t = 0; t<=T;t++)
	{
		h[t] = hwef(haar[t]);
		for(int i = 0; i<T;i++)
		{
			if(h[i] >0)
				wp+=w[i];
			if(h[i] <0)
				wn+=w[i];
			if (h[i] == 0)
				wz+=w[i];
			alpha[t] = (1/2)*logf((wp+(1/2)*wz)/((wn+(1/2)*wz)));
			Z=0;
			for(i=1;i<=nbpos+nbneg;i++)
				Z+=(w[i]*exp((-1)*alpha[t]*hwef((nbpos-i))*h[t]));
			for(int i=1;i<=nbpos+nbneg;i++)
				w[i] = (w[i]*exp((-1)*alpha[t]*hwef((nbpos-i))*h[t]))/Z;
			
		}
	}
	
	return 0;
} 
