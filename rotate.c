#include "rotate.h"
#include "array_utility.h"
#include "bilinear_interpolation.h"

#include <stdio.h>
#include <math.h>

float*** rotate (float*** input, int M_in, int N_in)
{
    // Prompt the user.
    float rotation_factor;
    printf("By how many degrees CCW do you want to rotate your image?\n");
    scanf("%f", &rotation_factor);
    printf("Rotating the input file...\n");

    // Prepare the output files.
    float*** output = alloc3df(3, M_in, N_in);

    // Define the center of the image.
    int vertical_center = floor(M_in / 2);
    int horizontal_center = floor(N_in / 2);

    // Loop through each pixel of the new image, select the new vertical
    // and horizontal positions, and interpolate the image to make the change.
    int i, j, k;
    for (i = 0; i < M_in; ++i) {
        for (j = 0; j < N_in; ++j) {
            //    // Figure out how rotated we want the image.
            double angle = rotation_factor * (double) Pi / 180;
            float vertical_position = (float) cos(angle) *
                (i - vertical_center) + sin(angle) * (j - horizontal_center)
                + vertical_center;
            float horizontal_position = (float) -sin(angle) *
                (i - vertical_center) + cos(angle) * (j - horizontal_center)
                + horizontal_center;

            // Figure out the four locations (and then, four pixels)
            // that we must interpolate from the original image.
            int top = floor(vertical_position);
            int bottom = top + 1;
            int left = floor(horizontal_position);
            int right = left + 1;

            // Check if any of the four locations are invalid. If they are,
            // skip interpolating this pixel. Otherwise, interpolate the
            // pixel according to the dimensions set above and set the
            // resulting pixel.
            if (top >= 0 && bottom < M_in && left >= 0 && right < N_in ) {
                for (k = 0; k < 3; k++) {
                    float interpolated = bilinearly_interpolate(top, bottom,
                        left, right, horizontal_position, vertical_position,
                        input[k]);
                        output[k][i][j] = interpolated;
                }
            }
        }
    }

    return output;
}