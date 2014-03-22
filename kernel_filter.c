#include "kernel_filter.h"
#include "array_utility.h"

#include <math.h>
#include <stdio.h>

// Array addition.
float** add (float** arrayOne, float** arrayTwo, int row, int col)
{
    int i, j;
    float** final = alloc2df(row, col);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            final[i][j] = arrayOne[i][j] + arrayTwo[i][j];
        }
    }

    return final;
}

// Array subtraction.
float** subtract (float** arrayOne, float** arrayTwo, int row, int col)
{
    int i, j;
    float** final = alloc2df(row, col);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            final[i][j] = arrayOne[i][j] - arrayTwo[i][j];
        }
    }

    return final;
}

// Finds the surrounding pixel matrix in a given image.
float** find_pixel_matrix (float** input, int M_in, int N_in,
    int row, int col, int size)
{
    // Declare the pixel matrix.
    float** pixelMatrix = alloc2df(size, size);

    // Find the coordinates of the center pixel in the pixel matrix.
    int center = (int) floor((double) size / 2);

    // Fill in the surrounding edges relative to the center pixel.
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int pixelRow = row + (i - center);
            int pixelCol = col + (j - center);

            if (pixelRow < 0) {
                pixelRow = 0;
            }

            if (pixelRow > (M_in - 1)) {
                pixelRow = M_in - 1;
            }

            if (pixelCol < 0) {
                pixelCol = 0;
            }

            if (pixelCol > (N_in - 1)) {
                pixelCol = N_in - 1;
            }

            pixelMatrix[i][j] = input[pixelRow][pixelCol];
        }
    }

    return pixelMatrix;
}

// Convolution operation between two matrices.
float convolve_matrices (float** array_one, float** array_two, int size)
{
    int i, j;
    float sum = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            sum += array_one[i][j] * array_two[i][j];
        }
    }

    return sum;
}

// Convolution matrix filtering.
float*** convolve (float*** input, int M_in, int N_in, float** kernel, int dim)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);
    int i, j, k;

    // For each channel...
    for (k = 0; k < 3; k++) {
        // Find the pixel matrix for each pixel, convolve that matrix with the
        // given kernel, and use that result to determine the new value.
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                 N_in, i, j, dim);
                float new_value = convolve_matrices(pixel_matrix, kernel, dim);
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** lowpass_filter(float*** input, int M_in, int N_in)
{
    // Inform the user.
    printf("Performing a low-pass filter...\n");

    return convolve(input, M_in, N_in, lowpass_filter_3by3kernel(), 3);
}

float*** highpass_filter(float*** input, int M_in, int N_in)
{
    // Inform the user.
    printf("Performing a high-pass filter...\n");

    return convolve(input, M_in, N_in, highpass_filter_3by3kernel(), 3);
}

float** lowpass_filter_3by3kernel()
{
    float** kernel = alloc2df(3, 3);

    // Low-pass filter using 3x3 kernel.
    kernel[0][0] = (float) 1 * 1/16; kernel[0][1] = (float) 2 * 1/16;
        kernel[0][2] = (float) 1 * 1/16;
    kernel[1][0] = (float) 2 * 1/16; kernel[1][1] = (float) 4 * 1/16;
        kernel[1][2] = (float) 2 * 1/16;
    kernel[2][0] = (float) 1 * 1/16; kernel[2][1] = (float) 2 * 1/16;
        kernel[2][2] = (float) 1 * 1/16;

    return kernel;
}

float** highpass_filter_3by3kernel()
{
    // Define our 3 by 3 kernel.
    float** lpKernel = alloc2df(3, 3);
    lpKernel[0][0] = (float) 1 * 1/16; lpKernel[0][1] = (float) 2 * 1/16;
        lpKernel[0][2] = (float) 1 * 1/16;
    lpKernel[1][0] = (float) 2 * 1/16; lpKernel[1][1] = (float) 4 * 1/16;
        lpKernel[1][2] = (float) 2 * 1/16;
    lpKernel[2][0] = (float) 1 * 1/16; lpKernel[2][1] = (float) 2 * 1/16;
        lpKernel[2][2] = (float) 1 * 1/16;

    // Define our delta function kernel.
    float** deltaKernel = alloc2df(3, 3);
    deltaKernel[0][0] = (float) 0; deltaKernel[0][1] = (float) 0;
        deltaKernel[0][2] = (float) 0;
    deltaKernel[1][0] = (float) 0; deltaKernel[1][1] = (float) 1;
        deltaKernel[1][2] = (float) 0;
    deltaKernel[2][0] = (float) 0; deltaKernel[2][1] = (float) 0;
        deltaKernel[2][2] = (float) 0;

    // Subtract the latter from the former.
    return subtract(deltaKernel, lpKernel, 3, 3);
}
