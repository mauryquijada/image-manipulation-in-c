#include "histogram_equalization.h"
#include "array_utility.h"

#include <stdlib.h>

float*** equalize (float*** input, int M_in, int N_in)
{
    int option;

    // Prompt the user.
    printf("Which histgram specification would you like to apply? (1) for");
    printf(" a histogram that increases linearly in the lower half, but");
    printf(" decreases linearly in the upper half, (2) for a histogram that");
    printf(" decreases linearly in the lower half, but increases linearly");
    printf(" in the upper half.\n");
    scanf("%d", &option);

    switch (option) {
        case 1:
            return apply_convex_equalization(input, M_in, N_in);
        default:
            return apply_concave_equalization(input, M_in, N_in);
    }
}

float*** apply_concave_equalization (float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Create the desired density histogram.
    int i, j, k;
    int* desired_histogram = alloc1di(256);
    double* desired_histogram_count = alloc1dd(256);
    int total_pixels = 0;
    for (i = 0; i < 256; i++) {
        if (i < 129) {
            desired_histogram[i] = i;
        } else {
            desired_histogram[i] = 128 - i;
        }

        total_pixels += desired_histogram[i];
    }

    // Create the desired cumulative distribution for the above histogram.
    double fraction = 0.0;
    for (i = 0; i < 256; i++) {
        fraction += (double) desired_histogram[i] * (1 / (double)
            total_pixels);
        desired_histogram_count[i] = fraction;
    }

    // Prepare to calculate the cumulative histogram.
    double* pixel_count;
    int* new_histogram;
    float pixel_density = 1 / (float) (M_in * N_in);

    // Equalize the histogram on all three channels.
    for (k = 0; k < 3; k++) {
        pixel_count = alloc1dd(256);
        new_histogram = alloc1di(256);

        // Construct the current cumulative histogram.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                pixel_count[(int) input[k][i][j]] += pixel_density;
            }
        }

        // Create the lookup table for the new values of each grayscale color.
        j = 0;
        for (i = 0; i < 256; i++) {
            if (pixel_count[i] <= desired_histogram_count[j]) {
                new_histogram[i] = j;
            } else {
                while (pixel_count[i] > desired_histogram_count[j]) {
                    j++;
                }
                if (desired_histogram_count[j] - pixel_count[i] >
                        pixel_count[i] - desired_histogram_count[j - 1]) {
                    new_histogram[i] = j - 1;
                } else {
                    new_histogram[i] = j;
                }
            }
        }

        // Create the new image.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                output[k][i][j] = new_histogram[(int) input[k][i][j]];
            }
        }
        free(pixel_count);
        free(new_histogram);
    }

    free(desired_histogram);
    return output;
}

float*** apply_convex_equalization (float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Create the desired density histogram.
    int i, j, k;
    int* desired_histogram = alloc1di(256);
    double* desired_histogram_count = alloc1dd(256);
    int total_pixels = 0;
    for (i = 0; i < 256; i++) {
        if (i < 129) {
            desired_histogram[i] = 128 - i;
        } else {
            desired_histogram[i] = i - 128;
        }

        total_pixels += desired_histogram[i];
    }

    // Create the desired cumulative distribution for the above histogram.
    double fraction = 0.0;
    for (i = 0; i < 256; i++) {
        fraction += (double) desired_histogram[i] * (1 / (double)
            total_pixels);
        desired_histogram_count[i] = fraction;
    }

    // Prepare to calculate the cumulative histogram.
    double* pixel_count;
    int* new_histogram;
    float pixel_density = 1 / (float) (M_in * N_in);

    // Equalize the histogram on all three channels.
    for (k = 0; k < 3; k++) {
        pixel_count = alloc1dd(256);
        new_histogram = alloc1di(256);

        // Construct the current cumulative histogram.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                pixel_count[(int) input[k][i][j]] += pixel_density;
            }
        }

        // Create the lookup table for the new values of each grayscale color.
        j = 0;
        for (i = 0; i < 256; i++) {
            if (pixel_count[i] <= desired_histogram_count[j]) {
                new_histogram[i] = j;
            } else {
                while (pixel_count[i] > desired_histogram_count[j]) {
                    j++;
                }
                if (desired_histogram_count[j] - pixel_count[i] >
                        pixel_count[i] - desired_histogram_count[j - 1]) {
                    new_histogram[i] = j - 1;
                } else {
                    new_histogram[i] = j;
                }
            }
        }

        // Create the new image.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                output[k][i][j] = new_histogram[(int) input[k][i][j]];
            }
        }
        free(pixel_count);
        free(new_histogram);
    }

    free(desired_histogram);
    return output;
}
