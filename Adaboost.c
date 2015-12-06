#include "Adaboost.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

StrongClassifier AdaBoost (SDL_Surface** images,int nbpos, int nbneg,int T) {
	int nbimages = nbpos+nbneg;
	StrongClassifier sc;
        sc.count = 0;
	struct Matrix* im = malloc(nbimages*sizeof(struct Matrix));
	for(int i = 0; i<nbimages;i++)
	{
		convertToMatrix((im[i]),images[i]);
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
	//WeakClassifier* Cls = malloc(162336*sizeof(WeakClassifier));
	WeakClassifier k;
	int idx;
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
					min_error = k.error;
					idx = j;
				}
			}
		}
		k.alpha = (1/2)*logf((1-k.error)/k.error);
		sc.weaks[sc.count] = k;
		sc.count++;
		for(int i = 0;i<nbpos;i++)
		{
			if(Cls[i][idx].Haar.Haar>0)
				w[i] *= exp(-k.alpha);
			else
				w[i] *= exp(k.alpha);
		}
		for(int i = nbpos;i<nbimages;i++)
		{
			if(Cls[i][idx].Haar.Haar<0)
				w[i] *= exp(-k.alpha);
			else
				w[i] *= exp(k.alpha);
		}
	}
	return sc;
}


