#include "contrast_enhancement.h"
#include "histograms.h"
#include "array_utility.h"

#include <stdlib.h>

float*** enhance_contrast (float*** input, int M_in, int N_in)
{
    int option;
    // Prompt the user.
    printf("Which histogram stretch would you like to perform? (1) for");
    printf(" a linear stretch, (2) for a 3%% min-max linear stretch.\n");
    scanf("%d", &option);

    switch (option) {
        case 2:
            return min_max_stretch(input, M_in, N_in, 0.03);
        default:
            return linear_stretch(input, M_in, N_in);
    }
}

float*** linear_stretch (float*** input, int M_in, int N_in)
{
    // Define output.
    float*** output = alloc3df(3, M_in, N_in);
    float** densityHistogram;

    int minColor, maxColor;
    int i, j, k;

    // Linearly stretch for all colors.
    for (k = 0; k < 3; k++) {
        // Reset necessary variables.
        minColor = 0;
        maxColor = 255;

        // Create a histogram of the input.
        densityHistogram = generate_density_histogram(input[k], 256,
            M_in, N_in);

        // Find the minimum and maximum pixel using the original histogram by
        // looping through the columns and checking for the first row that
        // has a value greater than 0.
        for (i = 0; i < 256; i++) {
            if (densityHistogram[255][i] > 0.0) {
                minColor = i + 1;
                break;
            }
        }
        for (i = 256 - 1; i > 0; i--) {
            if (densityHistogram[255][i] > 0.0) {
                maxColor = i + 1;
                break;
            }
        }

        // Create the new image with this information.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                // Set any pixel that has < minimum equal to zero, and set
                // any pixel that has > maximum equal to zero.
                if (input[k][i][j] < minColor) {
                    output[k][i][j] = 0;
                } else if (input[k][i][j] > maxColor) {
                    output[k][i][j] = 255;
                } else {
                    // Create the resulting pixel based on a linear scaling factor
                    // that takes into account the min and max.
                    output[k][i][j] = ((input[k][i][j] - minColor) /
                        (maxColor - minColor)) * 255;
                }
            }
        }

        free(densityHistogram);
    }

    return output;
}

float*** min_max_stretch (float*** input, int M_in, int N_in, double cutoff)
{
    // Define output.
    float*** output = alloc3df(3, M_in, N_in);
    float* density;
    float* cumulative;

    int minColor, maxColor;
    int i, j, k;
    // Linearly stretch for all three colors.
    for (k = 0; k < 3; k++) {
        minColor = 0;
        maxColor = 255;

        // Define the density and cumulative distribution functions.
        density = alloc1df(256);
        cumulative = alloc1df(256);

        // Define the weight of each pixel.
        float weight = (float) 1.0 / M_in / N_in;

        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                density[(int) input[k][i][j]] += weight;
            }
        }

        // Populate the cumulative distribution function.
        cumulative[0] = density[0];
        for (i = 1; i < 256; i++) {
            cumulative[i] += cumulative[i - 1] + density[i];
        }

        float w = 0;
        while (w < cutoff) {
            w += density[minColor++];
        }

        w = 0;
        while (w < cutoff) {
            w += density[maxColor--];
        }

        // Create the new image with this information.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                // Set any pixel that has < minimum equal to zero, and set
                // any pixel that has > maximum equal to zero.
                if (input[k][i][j] < minColor) {
                    output[k][i][j] = 0;
                } else if (input[k][i][j] > maxColor) {
                    output[k][i][j] = 255;
                } else {
                    // Create the resulting pixel based on a linear scaling factor
                    // that takes into account the min and max.
                    output[k][i][j] = ((input[k][i][j] - minColor) /
                        (maxColor - minColor)) * 255;
                }
            }
        }

        // Free memory.
        free(density);
        free(cumulative);
    }

    return output;
}
