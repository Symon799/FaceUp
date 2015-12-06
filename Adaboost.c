#include "pixel_operations.h"
#include "integral.h"
#include "Adaboost.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define MAX_CLS_IN_STAGE 30

/*int pos_count,neg_count;
float[] w;


*/
/*long ApplyFeature(SDL_image *image,int type, int posx, int posy, int longueur, int largeur)
{
	switch(type)
	{
		case 1 : return (RecSum(mat,posx,poxy,posx+longueur-1,posy+largeur-1) 
			- RecSum(mat,posx,posy+longueur,posx+longueur-1,posy+2*largeur-1));
				
		case 2 : return (RecSum(mat,posx,posy,posx+longueur-1,posy+largeur-1)
			- RecSum(mat,posx,posy+largeur,posx+longueur-1,posy+2*largeur-1)
			+ RecSum(mat,posx,posy+2*largeur,posx+longueur-1,posy+3*largeur-1));

		case 3 : return (RecSum(mat,posx,posy,posx+longueur-1,posy+largeur-1)
				- RecSum(mat,posx+longueur,posy,posx+2*longueur-1,posy+largeur-1));

		case 4 : return (RecSum(mat,posx,posy,posx+longueur-1,posy+largeur-1)
				- RecSum(mat,posx+longueur,posy,posx+2*longueur-1,posy+largeur-1)
				+ RecSum(mat,posx+2*longueur,posy,posx+3*longueur-1,posy+largeur-1));

		default : return (RecSum(mat,posx,posy,posx+longueur-1,posy+largeur-1)
				- RecSum(mat,posx+longueur,posy,posx+2*longueur-1,posy+largeur-1)
				- RecSum(mat,posx,posy+largeur,posx+longueur-1,posy+2*largeur-1)
				+ RecSum(mat,posx+longueur,posy+largeur,posx+2*longueur-1,posy+2*largeur-1);
	}
}


int sum (int *tbl, int len) {
        
      	int sum=0;
        while(len>0)
	{
                sum+=tbl[len-1];
		len--;
	}
        return sum;
}

void MakeVector(int **img, int *vec, int w, int h)
{
        for (int j=0; j<w; j++)
                for(int i=0; i<h; i++)
                        vec[i*w + j] = img[i][j];
}

// MakeArray: img is a vector with cols placed one after another

int **MakeArray(int *img, int w, int h)
{
        int **arr = malloc(h*sizeof(int));
        for(int i=0; i<h; i++)
	{
                arr[i] = malloc(w*sizeof(int));

        	for (int j=0; j<w; j++)
                        arr[i][j] = img[j*h + i];
	}
        return arr;
}


double ApplyFeature(int *f, int *img)
{
        /// f & img have to be vectors, really.
        /// of size 24*24
        double wynik = 0;
        for(int i=0; i<576; i++)
        {
                                wynik+= f[i]*img[i];
        }
        return wynik;
}


WeakClassifier findWeakClassifier(int *f, int *fxIdx) {
        
        double e1 = 0, e2 = 0, Tp, Tn, Sp, Sn;
        int min1Idx, min2Idx, i, j;
        WeakClassifier cls;
        
        for(i=0; i<pos_count; i++)
                Tp += w[i];
        for(i=pos_count; i<(pos_count+neg_count); i++)
                Tn += w[i];
        e2 = 1;
        double min1 = e1, min2 = e2;
        for(i=0; i<(pos_count+neg_count); i++)
        {
                if(labels[i]==1)
                        Sp += w[fxIdx[i]];
                else
                        Sn += w[fxIdx[i]];
                
                e1 = ( Sp + (Tn - Sn));
                e2 = ( Sn + (Tp - Sp));
                        
                if(e1<min1)
                {
                        min1 = e1;
                        min1Idx = i;
                }
                if(e2<min2)
                {
                        min2 = e2;
                        min2Idx = i;
                }
        }
        
        if(min1<min2)
        {
                cls.parity = 1;
                cls.theta = ApplyFeature(f, images[fxIdx[min1Idx]]);
                cls.error = min1;
        }
        else
        {
                cls.parity = -1;
                cls.theta = ApplyFeature(f, images[fxIdx[min2Idx]]);
                cls.error = min2;
        }
        
}*/


StrongClassifier AdaBoost (SDL_Surface** images,int nbpos, int nbneg,int T) {
	int nbimages = nbpos+nbneg;
	StrongClassifier sc;
        sc.count = 0;
	struct Matrix* im = malloc(nbimages*sizeof(struct Matrix));
	for(int i = 0; i<nbimages;i++)
	{
		convertToMatrix(&(im[i]),images[i]);
		im[i].x = images[i]->h;
		im[i].y = images[i]->w;
	}
	float *w = malloc(nbimages*sizeof(float));
	for(int i = 0; i<nbimages;i++)
		w[i] = 1/nbimages;
	feat** f = malloc(nbimages*sizeof(feat*));
	for(int i =0; i<nbimages;i++)
		f[i] = Haar(im[i],0,0,24);
	WeakClassifier** Cls = malloc(nbimages*sizeof(WeakClassifier*));
	WeakClassifier k;
	for(int t = 0; t<T;t++)
	{
		for(int i =0; i<nbimages;i++)
		{
			for(int j = 0;j<162336;j++)
			{
				Cls[i][j].Haar = f[i][j];
				Cls[i][j].alpha = 0;
				Cls[i][j].error = 0;
				Cls[i][j].used = false;
				if(!((f[i][j].Haar >=0 && i<nbpos) || (f[i][j].Haar <0 && i>=nbpos)))
					Cls[i][j].error+= w[i];
			}
		}
		int min_error = Cls[0][0].error;
		for(int i = 0;i<nbimages;i++)
		{
			for(int j = 0;j<162336;j++)
			{
				if(Cls[i][j].error<min_error && !Cls[i][j].used)
				{
					k = Cls[i][j];
					min_error = Cls[i][j].error;
				}
			}
		}
		k.alpha = logf((1-k.error)/k.error);
		sc.weaks[sc.count] = k;
		sc.count++;
	}
	return sc;
}


