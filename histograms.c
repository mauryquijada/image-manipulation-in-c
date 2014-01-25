#include "histograms.h"
#include "array_utility.h"

#include <stdio.h>
#include <stdlib.h>

// Helper function that returns the maximum value in an array of integers.
int max_value (int* array, int num_elements)
{
    int i, max = -32000;
    for (i = 0; i < num_elements; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

float** generate_density_histogram (float** input, int size, int M_in,
    int N_in)
{
    printf("Generating a density histogram...\n");
    // Instantiate counting variables used in for loops and the return
    // variable.
    int i, j;
    float** output = alloc2df(size, size);

    // Count the grayscale color present in each pixel.
    int* count = alloc1di(size);

    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            count[(int) input[i][j]]++;
        }
    }

    // Scale the images by making a ratio of (the count / the largest
    // count) and multiply by the total size of our histogram.
    double max = (double) max_value(count, size);

    for (i = 0; i < size; i++) {
        count[i] = (count[i] / max) * size;
    }

    // Create the density histogram.
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            float value;

            if (255 - i < count[j]) {
                value = 255.0;
            } else {
                value = 0.0;
            }
            output[i][j] = value;
        }
    }

    // Deallocate memory.
    free(count);

    return output;
}

float** generate_cumulative_histogram (float** img, int size, int M_in,
    int N_in)
{
    printf("Generating a cumulative histogram...\n");

    // Instantiate counting variables used in for loops and the return
    // variable.
    int i, j;
    float** output = alloc2df(size, size);

    // Create the cumulative histogram count.
    double* count = alloc1dd(size);
    float density = 1 / (float) (M_in * N_in);

    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            count[(int) img[i][j]] += density;
        }
    }

    // Enable cumulation.
    double total = 0.0;
    for (i = 0; i < size; i++) {
        total += count[i];
        count[i] = total * size;
    }

    // Create the cumulative histogram.
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            float value;

            if (255 - i < count[j]) {

                value = 255.0;
            } else {
                value = 0.0;
            }
            output[i][j] = value;
        }
    }

    // Deallocate memory.
    free(count);

    return output;
}

