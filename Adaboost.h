typedef int bool;
#define true 1
#define false 0

#include "pixel_operations.h"
#include "integral.h"
#include "haar.h"

typedef struct {
        feat Haar;
	int error;
	float alpha;
	bool used;
} WeakClassifier;

typedef struct {
	WeakClassifier weaks[20];
	int count;
} StrongClassifier;

StrongClassifier AdaBoost (SDL_Surface** images,int nbpos, int nbneg,int T);

