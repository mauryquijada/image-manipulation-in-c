#include "median_filter.h"
#include "array_utility.h"
#include "kernel_filter.h"

#include <math.h>

// Helper function to find the pixel array for a particular input image.
float* find_pixel_array (float** input, int M_in, int N_in,
    int row, int col, int size, int* array_size)
{
    // Declare array size.
    *array_size = size * size;

    // Declare the pixel array.
    float* array = alloc1df(*array_size);
    int index = 0;

    // Find the coordinates of the center pixel in the pixel matrix.
    int center = (int) floor((double) size / 2);

    // Fill in the surrounding edges relative to the center pixel.
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int pixel_row = row + (i - center);
            int pixel_col = col + (j - center);

            if (pixel_row < 0) {
                pixel_row = 0;
            }

            if (pixel_row > (M_in - 1)) {
                pixel_row = M_in - 1;
            }

            if (pixel_col < 0) {
                pixel_col = 0;
            }

            if (pixel_col > (N_in - 1)) {
                pixel_col = N_in - 1;
            }

            array[index++] = input[pixel_row][pixel_col];
        }
    }

    return array;
}

// Helper function to find the cross array for a particular input image.
float* find_cross_array (float** input, int M_in, int N_in,
    int row, int col, int width, int height, int* array_size)
{
    // Declare the pixel matrix and the index on which we're currently iterating.
    *array_size = width * 2 + height * 2;
    float* cross_array = alloc1df(*array_size);
    int current_index = 0;

    // Find the horizontal elements of the cross.
    int i, j;
    for (i = 0; i < width * 2; i++) {
        int pixel_row = row + (i - width);
        int pixel_col = col;

        if (pixel_row < 0) {
            pixel_row = 0;
        }

        if (pixel_row > (M_in - 1)) {
            pixel_row = M_in - 1;
        }

        cross_array[current_index++] = input[pixel_row][pixel_col];
    }

    // Find the vertical elements of the cross.
    for (j = 0; j < height * 2; j++) {
        int pixel_row = row;
        int pixel_col = col + (j - height);

        if (pixel_col < 0) {
            pixel_col = 0;
        }

        if (pixel_col > (N_in - 1)) {
            pixel_col = N_in - 1;
        }

        cross_array[current_index++] = input[pixel_row][pixel_col];
    }

    return cross_array;
}

float*** median_filter (float*** input, int M_in, int N_in)
{
    // Prompt the user.
    printf("What shape would you like to use for the median filter's window?");
    printf(" (1) for cross, (2) for square.\n");
    int option;
    scanf("%d", &option);

    float*** output;
    switch (option) {
        case 2:
            printf("Performing a square-shaped median filter...\n");
            output = square_median_filter(input, M_in, N_in);
            break;
        default:
            printf("Performing a cross-shaped median filter...\n");
            output = cross_median_filter(input, M_in, N_in);
            break;
    }

    return output;
}

float*** square_median_filter (float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Decide the window of a 2D median filter to be an 3 by 3 pixel array.
    int size = 3;

    int i, j, k, l, m;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                int array_size;
                float* square = find_pixel_array(input[k], M_in, N_in, i,
                    j, size, &array_size);

                // Sort the resulting set of pixels.
                for (m = 0; m < array_size - 1; m++) {
                    for (l = m + 1; l < array_size; l++) {
                        if (square[m] > square[l]) {
                            float swap = square[m];
                            square[m] = square[l];
                            square[l] = swap;
                        }
                    }
                }

                // Replace the pixel that we're evaluating with the median
                // pixel.
                int center = (int) floor((double) array_size / 2);
                output[k][i][j] = square[center];
            }
        }
    }

    return output;
}

float*** cross_median_filter (float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Decide the window of a 2D median filter to be a cross that extends
    // 4 pixels W and E and 4 pixels N and S.
    int width = 4;
    int height = 4;

    int i, j, k, l, m;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                int array_size;
                float* cross = find_cross_array(input[k], M_in, N_in, i, j,
                    width, height, &array_size);

                // Sort the resulting set of pixels.
                for (m = 0; m < array_size - 1; m++) {
                    for (l = m + 1; l < array_size; l++) {
                        if (cross[m] > cross[l]) {
                            float swap = cross[m];
                            cross[m] = cross[l];
                            cross[l] = swap;
                        }
                    }
                }

                // Replace the pixel that we're evaluating with the median
                // pixel.
                int center = (int) floor((double) array_size / 2);
                output[k][i][j] = cross[center];
            }
        }
    }

    return output;
}
