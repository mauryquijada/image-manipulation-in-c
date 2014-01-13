#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_utility.h"
#include "rotate.h"
#include "resize.h"
#include "histograms.h"

int main ()
{
	char panda_name[50];
	float** panda;
	int panda_M, panda_N;

	printf("Hello world!");

	strcpy(panda_name, "panda.pgm");

    // Read in the black and white images.
    panda = read_bw_image(panda_name, &panda_M, &panda_N);
}