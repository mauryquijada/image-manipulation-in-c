#include "edge_detection.h"
#include "array_utility.h"
#include "kernel_filter.h"
#include "contrast_enhancement.h"
#include "median_filter.h"

float*** apply_Laplacian_of_Gaussian (float*** input, int M_in, int N_in,
    float threshold, int square_size)
{
    // Declare output.
    float** intermediate = alloc2df(M_in, N_in);
    float*** output = alloc3df(3, M_in, N_in);

    // Define the Laplacian of Gaussian kernel.
    float** kernel = alloc2df(5, 5);
    kernel[0][0] = 0;  kernel[0][1] = 0; kernel[0][2] = 1; kernel[0][3] = 0;
        kernel[0][4] = 0;
    kernel[1][0] = 0;  kernel[1][1] = 1; kernel[1][2] = 2; kernel[1][3] = 1;
        kernel[1][4] = 0;
    kernel[2][0] = 1;  kernel[2][1] = 2; kernel[2][2] = -16; kernel[2][3] = 2;
        kernel[2][4] = 1;
    kernel[3][0] = 0;  kernel[3][1] = 1; kernel[3][2] = 2; kernel[3][3] = 1;
        kernel[3][4] = 0;
    kernel[4][0] = 0;  kernel[4][1] = 0; kernel[4][2] = 1; kernel[4][3] = 0;
        kernel[4][4] = 0;

    int i, j, k, l, m;
    for (k = 0; k < 3; k++) {
        // Find the pixel matrix for each pixel, multiply that matrix with the one
        // above, and set the array combination of the two equal to the currently
        // processed pixel.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixelMatrix = find_pixel_matrix(input[k], M_in, N_in,
                    i, j, 5);
                float newValue = convolve_matrices(pixelMatrix, kernel, 5);
                intermediate[i][j] = newValue;
            }
        }

        // Find zerocrossings and eliminate noise (given pseudocode).
        for (i = 0; i < M_in - square_size; i++) {
            for (j = 0; j < N_in - square_size; j++) {
                float min = 9e9;
                float max = -min;

                for (m = 0; m < square_size; m++) {
                    for (l = 0; l < square_size; l++) {
                        float w = intermediate[i+m][j+l];
                        if (w < min) {
                            min = w;
                        }

                        if (w > max) {
                            max = w;
                        }
                    }
                }

                if (min < -threshold && max > threshold) {
                    output[k][i][j] = 254;
                } else {
                    output[k][i][j] = 0;
                }
            }
        }
    }

    return output;
}

float*** detect_edges (float*** input, int M_in, int N_in)
{
    printf("Applying a series of steps to detect edges in this image...\n");
    float*** lowpass_filtered = lowpass_filter(input, M_in, N_in);
    float*** linearly_stretched = min_max_stretch(lowpass_filtered, M_in, N_in, 0.50);
    float*** square_median_filtered = square_median_filter(linearly_stretched, M_in, N_in);
    float*** laplacian_of_gaussian =
        apply_Laplacian_of_Gaussian(square_median_filtered, M_in, N_in, 1, 3);

    dealloc3df(lowpass_filtered, 3, M_in, N_in);
    dealloc3df(linearly_stretched, 3, M_in, N_in);
    dealloc3df(square_median_filtered, 3, M_in, N_in);

    return laplacian_of_gaussian;
}
