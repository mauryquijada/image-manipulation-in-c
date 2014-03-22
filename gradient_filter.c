#include "gradient_filter.h"
#include "array_utility.h"
#include "kernel_filter.h"

#include <math.h>

float*** gradient_filter(float*** input, int M_in, int N_in)
{
    printf("Which gradient filter would you like to apply?\n");
    printf("1) Roberts operator.\n");
    printf("2) Sobel operator.\n");
    printf("3) Prewitt operator--3-by-3 kernel.\n");
    printf("4) Prewitt operator--5-by-5 kernel.\n");
    printf("5) Vertical operator.\n");
    printf("6) Horizontal operator.\n");
    printf("7) Diagonal operator (changes from Northwest direction).\n");
    printf("8) Diagonal operator (changes from Northeast direction).\n\n");
    int action;
    scanf("%d", &action);

    float*** output;
    switch (action) {
        case 2:
            printf("Applying the Sobel operator...\n");
            output = sobel_operator(input, M_in, N_in);
            break;
        case 3:
            printf("Applying the Prewitt operator with a 3-by-3 kernel...\n");
            output = prewitt_operator_3by3kernel(input, M_in, N_in);
            break;
        case 4:
            printf("Applying the Prewitt operator with a 5-by-5 kernel...\n");
            output = prewitt_operator_5by5kernel(input, M_in, N_in);
            break;
        case 5:
            printf("Applying the Vertical operator...\n");
            output = vertical_operator(input, M_in, N_in);
            break;
        case 6:
            printf("Applying the Horizontal operator...\n");
            output = horizontal_operator(input, M_in, N_in);
            break;
        case 7:
            printf("Applying the Diagonal operator (changes from Northwest direction)...\n");
            output = diagonal_compass_nw_operator(input, M_in, N_in);
            break;
        case 8:
            printf("Applying Diagonal operator (changes from Northeast direction)...\n");
            output = diagonal_compass_ne_operator(input, M_in, N_in);
            break;
        default:
            printf("Applying the Roberts operator...\n");
            output = roberts_operator(input, M_in, N_in);
            break;
    }

    return output;
}

float*** roberts_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = -1; kernel1[0][1] = 1; kernel1[0][2] = 0;
    kernel1[1][0] = 0;  kernel1[1][1] = 0; kernel1[1][2] = 0;
    kernel1[2][0] = 0;  kernel1[2][1] = 0; kernel1[2][2] = 0;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = -1; kernel2[0][1] = 0; kernel2[0][2] = 0;
    kernel2[1][0] = 1;  kernel2[1][1] = 0; kernel2[1][2] = 0;
    kernel2[2][0] = 0;  kernel2[2][1] = 0; kernel2[2][2] = 0;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** sobel_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = -1;  kernel1[0][1] = 0; kernel1[0][2] = 1;
    kernel1[1][0] = -2;  kernel1[1][1] = 0; kernel1[1][2] = 2;
    kernel1[2][0] = -1;  kernel1[2][1] = 0; kernel1[2][2] = 1;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = -1; kernel2[0][1] = -2; kernel2[0][2] = -2;
    kernel2[1][0] = 0;  kernel2[1][1] = 0;  kernel2[1][2] = 0;
    kernel2[2][0] = 1;  kernel2[2][1] = 2;  kernel2[2][2] = 1;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** prewitt_operator_3by3kernel(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = -1;  kernel1[0][1] = 0; kernel1[0][2] = 1;
    kernel1[1][0] = -1;  kernel1[1][1] = 0; kernel1[1][2] = 1;
    kernel1[2][0] = -1;  kernel1[2][1] = 0; kernel1[2][2] = 1;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = -1; kernel2[0][1] = -1; kernel2[0][2] = -1;
    kernel2[1][0] = 0;  kernel2[1][1] = 0;  kernel2[1][2] = 0;
    kernel2[2][0] = 1;  kernel2[2][1] = 1;  kernel2[2][2] = 1;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** prewitt_operator_5by5kernel(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(5, 5);
    kernel1[0][0] = -3;  kernel1[0][1] = -1; kernel1[0][2] = 1;
        kernel1[0][3] = 3; kernel1[0][4] = 0;
    kernel1[1][0] = -3;  kernel1[1][1] = -1; kernel1[1][2] = 1;
        kernel1[1][3] = 3; kernel1[1][4] = 0;
    kernel1[2][0] = -3;  kernel1[2][1] = -1; kernel1[2][2] = 1;
        kernel1[2][3] = 3; kernel1[2][4] = 0;
    kernel1[3][0] = -3;  kernel1[3][1] = -1; kernel1[3][2] = 1;
        kernel1[3][3] = 3; kernel1[3][4] = 0;
    kernel1[4][0] = 0;   kernel1[4][1] = 0;  kernel1[4][2] = 0;
        kernel1[4][3] = 0; kernel1[4][4] = 0;

    // Define our second kernel.
    float** kernel2 = alloc2df(5, 5);
    kernel2[0][0] = -3;  kernel2[0][1] = -3; kernel2[0][2] = -3;
        kernel2[0][3] = 3; kernel2[0][4] = 0;
    kernel2[1][0] = -1;  kernel2[1][1] = -1; kernel2[1][2] = -1;
        kernel2[1][3] = -1; kernel2[1][4] = 0;
    kernel2[2][0] = 1;  kernel2[2][1] = 1; kernel2[2][2] = 1;
        kernel2[2][3] = 1; kernel2[2][4] = 0;
    kernel2[3][0] = 3;  kernel2[3][1] = 3; kernel2[3][2] = 3;
        kernel2[3][3] = 3; kernel2[3][4] = 0;
    kernel2[4][0] = 0;  kernel2[4][1] = 0; kernel2[4][2] = 0;
        kernel2[4][3] = 0; kernel2[4][4] = 0;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 5);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 5);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 5);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** vertical_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = -1;  kernel1[0][1] = 0; kernel1[0][2] = 1;
    kernel1[1][0] = -1;  kernel1[1][1] = 0; kernel1[1][2] = 1;
    kernel1[2][0] = -1;  kernel1[2][1] = 0; kernel1[2][2] = 1;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = 1;  kernel2[0][1] = 0;  kernel2[0][2] = -1;
    kernel2[1][0] = 1;  kernel2[1][1] = 0;  kernel2[1][2] = -1;
    kernel2[2][0] = 1;  kernel2[2][1] = 0;  kernel2[2][2] = -1;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** horizontal_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = 1;  kernel1[0][1] = 1; kernel1[0][2] = 1;
    kernel1[1][0] = 0;  kernel1[1][1] = 0; kernel1[1][2] = 0;
    kernel1[2][0] = -1;  kernel1[2][1] = -1; kernel1[2][2] = -1;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = -1;  kernel2[0][1] = -1;  kernel2[0][2] = -1;
    kernel2[1][0] = 0;  kernel2[1][1] = 0;  kernel2[1][2] = 0;
    kernel2[2][0] = 1;  kernel2[2][1] = 1;  kernel2[2][2] = 1;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}

float*** diagonal_compass_nw_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = 0;  kernel1[0][1] = 1; kernel1[0][2] = 1;
    kernel1[1][0] = -1;  kernel1[1][1] = 0; kernel1[1][2] = 1;
    kernel1[2][0] = -1;  kernel1[2][1] = -1; kernel1[2][2] = 0;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = 0;  kernel2[0][1] = -1;  kernel2[0][2] = -1;
    kernel2[1][0] = 1;  kernel2[1][1] = 0;  kernel2[1][2] = -1;
    kernel2[2][0] = 1;  kernel2[2][1] = 1;  kernel2[2][2] = 0;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}


float*** diagonal_compass_ne_operator(float*** input, int M_in, int N_in)
{
    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Define our first kernel.
    float** kernel1 = alloc2df(3, 3);
    kernel1[0][0] = 1;  kernel1[0][1] = 1; kernel1[0][2] = 0;
    kernel1[1][0] = 1;  kernel1[1][1] = 0; kernel1[1][2] = -1;
    kernel1[2][0] = 0;  kernel1[2][1] = -1; kernel1[2][2] = -1;

    // Define our second kernel.
    float** kernel2 = alloc2df(3, 3);
    kernel2[0][0] = -1;  kernel2[0][1] = -1;  kernel2[0][2] = 0;
    kernel2[1][0] = -1;  kernel2[1][1] = 0;  kernel2[1][2] = 1;
    kernel2[2][0] = 0;  kernel2[2][1] = 1;  kernel2[2][2] = 1;

    // Find the pixel matrix for each pixel, determine our g_m and g_n, find
    // the magnitude, and set the new pixel equal to that value.
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < M_in; i++) {
            for (j = 0; j < N_in; j++) {
                float** pixel_matrix = find_pixel_matrix(input[k], M_in,
                    N_in, i, j, 3);
                float g_m = convolve_matrices(pixel_matrix, kernel1, 3);
                float g_n = convolve_matrices(pixel_matrix, kernel2, 3);

                float new_value = sqrt(pow(g_m, 2) + pow(g_n, 2));
                output[k][i][j] = new_value;
            }
        }
    }

    return output;
}
