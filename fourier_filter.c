#include "fourier_filter.h"
#include "array_utility.h"

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Discrete Fourier transform function. Courtesy of Prof. Ruye Wang of Harvey
// Mudd College (2013).
void discrete_fourier_transform(float xr[], float xi[], int N, int inverse)
{
    int i, j, k, m, n;
    float arg, s, c, *yr, *yi;

    if (inverse) {
        printf("IDFT of size %d \n",N);
    } else {
        printf("DFT of size %d \n",N);
    }

    yr = (float *) malloc(N*sizeof(float));
     yi = (float *) malloc(N*sizeof(float));

     // For all N frequency components
     for (k=0; k<N; k++) {
         yr[k] = yi[k] = 0;

         for (m=0; m<N; m++) {
             arg = -2 * M_PI * m * k / N;
             if (inverse) {
                 arg=-arg;
             }

             c = cos(arg);
             s = sin(arg);
              yr[k] += xr[m] * c - xi[m] * s;
              yi[k] += xi[m] * c + xr[m] * s;
          }
    }

    arg = 1.0 / sqrt((float) N);

    for (k=0; k<N; k++) {
        xr[k] = yr[k] * arg;
        xi[k] = yi[k] * arg;
     }
}

float*** fourier_filter(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}
