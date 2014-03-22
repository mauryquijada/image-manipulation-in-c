#include "fourier_filter.h"
#include "array_utility.h"

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr

// Discrete Fourier transform function. Courtesy of Prof. Ruye Wang of Harvey
// Mudd College (2013).
// Note that N _must_ be a power of 2.
void discrete_fourier_transform(float xr[], float xi[], int N, int inverse)
{
    int mmax, step, i, j, k, j1, m, n;
    float arg, s, c, w, tempr, tempi;

    m = log((float) N) / log(2.0);

    // Perform bit reversal.
    for (i = 0; i < N; ++i) {
        j = 0;

        for (k=0; k<m; ++k) {
            j = (j << 1) | (1 & (i >> k));
        }

        if (j < i) {
            SWAP(xr[i],xr[j]);
            SWAP(xi[i],xi[j]);
        }
      }

     // For log N stages.
     for (i = 0; i < m; i++) {
        n = w = pow(2.0,(float) i);
        w = M_PI / n;

        if (inverse) {
            w=-w;
        }

        k = 0;

        // For N components.
        while (k < N - 1) {
            // For each section.
            for (j=0; j<n; j++) {
                arg =- j * w;
                c = cos(arg);
                s = sin(arg);
                j1 = k + j;
                tempr = xr[j1 + n]* c- xi[j1 + n] * s;
                tempi = xi[j1 + n]* c+ xr[j1 + n] * s;
                xr[j1+n] = xr[j1] - tempr;
                xi[j1+n] = xi[j1] - tempi;
                xr[j1] = xr[j1] + tempr;
                xi[j1] = xi[j1] + tempi;
              }

              k += 2 * n;
        }
    }

    arg = 1.0 / sqrt((float) N);

    for (i = 0; i < N; i++) {
        xr[i] *= arg;
        xi[i] *= arg;
    }
}

float*** fourier_filter(float*** input, int M_in, int N_in)
{
    // Prompt the user.
    printf("Which types of frequencies would you like to filter? (1) for");
    printf(" low frequencies, (2) for high frequencies.\n");
    int option;
    scanf("%d", &option);

    int high;
    switch (option) {
        case 2:
            printf("Performing a Fourier filter on high frequencies...\n");
            high = 1;
            break;
        default:
            printf("Performing a Fourier filter on low frequencies...\n");
            high = 0;
            break;
    }

    // Inform the user.
    printf("Carrying out the 2D Fourier transform of the image...\n");

    // Define a new image such that the dimensions are powers of 2.
    // This is to ensure that the image works with the Fast Fourier
    // Transform algorithm.
    int M_in_new, N_in_new;
    M_in_new = pow(2, ceil(log((float) M_in) / log(2.0)));
    N_in_new = pow(2, ceil(log((float) N_in) / log(2.0)));

    // Declare necessary variables.
    float**** input_fourier_series = alloc4df(3, M_in_new, N_in_new, 2);
    float*** output = alloc3df(3, M_in_new, N_in_new);

    // Make a copy of the input so as to preserve the original copy.
    float*** input_working_copy = alloc3df(3, M_in_new, N_in_new);
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                input_working_copy[k][i][j] = input[k][i][j];
            }
        }
    }

    // Perform a 2D Fourier transform.
    // Perform first for each column in the x-direction.
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in_new; i++) {
            // Create an empty array so that our DFT function can put the
            // imaginary numbers.
            float* imaginary = alloc1df(N_in_new);

            // Transform.
            discrete_fourier_transform(input_working_copy[k][i], imaginary,
                N_in_new, 0);

            // Preserve the transform in an array.
            for (j = 0; j < N_in_new; j++) {
                input_fourier_series[k][i][j][0] = input_working_copy[k][i][j];
                input_fourier_series[k][i][j][1] = imaginary[j];
            }
        }
    }

    // Perform then for each row in the y-direction.
    // Note that this involves the extra step of making sure that row
    // has its pixels in a sequential row before taking the DFT.
    for (k = 0; k < 3; k++) {
        for (j = 0; j < N_in_new; j++) {
            float* real = alloc1df(M_in_new);
            float* imaginary = alloc1df(M_in_new);

            for (i = 0; i < M_in_new; i++) {
                real[i] = input_fourier_series[k][i][j][0];
                imaginary[i] = input_fourier_series[k][i][j][1];
            }

            // Transform.
            discrete_fourier_transform(real, imaginary, M_in_new, 0);

            // Preserve the transform in an array.
            for (i = 0; i < M_in_new; i++) {
                input_fourier_series[k][i][j][0] = real[i];
                input_fourier_series[k][i][j][1] = imaginary[i];
            }

            // Release "real" and "imaginary" memory.
            free(real);
            free(imaginary);
        }
    }

    // Create the low-pass filter here as a circle. The
    // high-pass filter will just be the opposite of that. Note that
    // this assumes that the zero-frequency component is at the center
    // of the array.
    float** low_pass_spectrum_plot = alloc2df(M_in_new, N_in_new);
    for (i = 0; i < M_in_new; i++) {
        for (j = 0; j < N_in_new; j++) {
            if (sqrt(pow(i - floor(M_in_new / 2), 2) +
                pow(j - floor(N_in_new / 2), 2)) < 10) {
                low_pass_spectrum_plot[i][j] = 1;
            }
        }
    }

    // Shift the low-pass filter to match the format of the
    // format we've produced (moving the zero-frequency from the center
    // to the edges.
    float swap;
    for (i = 0; i < floor(M_in_new / 2); i++) {
        for (j = 0; j < N_in_new; j++) {
            int i_i = (int) floor(i + M_in_new / 2) % M_in_new;
            int i_j = (int) floor(j + N_in_new / 2) % N_in_new;

            swap = low_pass_spectrum_plot[i][j];

            low_pass_spectrum_plot[i][j] = low_pass_spectrum_plot[i_i][i_j];
            low_pass_spectrum_plot[i_i][i_j] = swap;
           }
    }

    // Create the frequency spectrums for the low-pass and high-pass images.
    // Note that the high-pass is just the inverse of the low-pass.
    float real, im;
    float**** desired_image_spectrum = alloc4df(3, M_in_new, N_in_new, 2);

    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in_new; i++) {
            for (j = 0; j < N_in_new; j++) {
                real = im = 0;

                if (low_pass_spectrum_plot[i][j] > 0.00000001) {
                    if (high == 0) {
                        real = input_fourier_series[k][i][j][0];
                        im = input_fourier_series[k][i][j][1];
                    }
                } else {
                    if (high == 1) {
                        real = input_fourier_series[k][i][j][0];
                        im = input_fourier_series[k][i][j][1];
                    }
                }

                desired_image_spectrum[k][i][j][0] = real;
                desired_image_spectrum[k][i][j][1] = im;
            }
        }
    }

    // Inform the user.
    printf("Carrying out the inverse 2D Fourier transform of the image...\n");

    // Store the imaginary values returned in the following intermediate
    // step.
    float*** imaginary_y = alloc3df(3, M_in_new, N_in_new);

    // Perform first for each row in the y-direction.
    // Note that this involves the extra step of making sure that row
    // has its pixels in a sequential row before taking the DFT.
    for (k = 0; k < 3; k++) {
        for (j = 0; j < N_in_new; j++) {
            float* real = alloc1df(M_in_new);
            float* imaginary = alloc1df(M_in_new);

            for (i = 0; i < M_in_new; i++) {
                real[i] = desired_image_spectrum[k][i][j][0];
                imaginary[i] = desired_image_spectrum[k][i][j][1];
            }

            // Inverse transform.
            discrete_fourier_transform(real, imaginary, M_in_new, 1);

            for (i = 0; i < M_in_new; i++) {
                output[k][i][j] = real[i];
                imaginary_y[k][i][j] = imaginary[i];
            }

            // Release "real" and "imaginary" memory.
            free(real);
            free(imaginary);
        }
    }

    // Perform then for each column in the x-direction.
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in_new; i++) {
            discrete_fourier_transform(output[k][i], imaginary_y[k][i], N_in_new, 1);
        }
    }

    return output;
}
