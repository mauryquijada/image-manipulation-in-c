#include "resize.h"
#include "bilinear_interpolation.h"
#include "array_utility.h"

#include <math.h>

float** resize (float** input, int M_in, int N_in)
{
    // Prompt the user.
    float verti_resize_factor, horiz_resize_factor;
    printf("By what factor do you want to scale your image horizontally?\n");
    scanf("%f", &horiz_resize_factor);
    printf("By what factor do you want to scale your image vertically?\n");
    scanf("%f", &verti_resize_factor);

    printf("Resizing...\n");

    // Figure out the dimensions of the new, resized image and define the
    // new array.
    int M_out_resized = M_in * verti_resize_factor;
    int N_out_resized = N_in * horiz_resize_factor;
    float** output = alloc2df(M_out_resized, N_out_resized);

    // Loop through each pixel of the new image and interpolate the pixels
    // based on what's in the input image.
    int i, j;
    for (i = 0; i < M_out_resized; ++i) {
        for (j = 0; j < N_out_resized; ++j) {
            // Figure out how far down or across (in percentage) we are with
            // respect to the original image.
            float vertical_position = i * ( (float) M_in / M_out_resized);
            float horizontal_position = j * ( (float) N_in / N_out_resized);

            // Figure out the four locations (and then, four pixels)
            // that we must interpolate from the original image.
            int top = floor(vertical_position);
            int bottom = top + 1;
            int left = floor(horizontal_position);
            int right = left + 1;

            // Check if any of the four locations are invalid. If they are,
            // simply access the valid adjacent pixel.
            if (bottom >= M_in) {
                bottom = top;
            }
            if (right >= N_in) {
                right = left;
            }

            // Interpolate the pixel according to the dimensions
            // set above and set the resulting pixel.
            float interpolated = bilinearly_interpolate(top, bottom, left,
                right, horizontal_position, vertical_position, input);
            output[i][j] = interpolated;
        }
    }

    return output;
}