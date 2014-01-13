#include "rotate.h"
#include "bilinear_interpolation.h"

float** rotate (float** input, int M_in, int N_in)
{
    // Prompt the user.
    printf("By how many degrees CCW do you want to rotate your image?\n");
    scanf("%f", &rotation_factor);
    printf("Rotating the input file...\n");

    // Prepare the output files.
    output = alloc2df(M_in, N_in);

    // Define the center of the image.
    int vertical_center = floor(M_out_rotated / 2);
    int horizontal_center = floor(N_out_rotated / 2);

    // Loop through each pixel of the new image, select the new vertical
    // and horizontal positions, and interpolate the image to make the change.
    int row, col;
    for (row = 0; row < M_out_rotated; ++row) {
        printf(" .");
        for (col = 0; col < N_out_rotated; ++col) {
            //    // Figure out how rotated we want the image.
            double angle = rotation_factor * (double) Pi / 180;
            float vertical_position = (float) cos(angle) *
                (row - vertical_center) + sin(angle) * (col - horizontal_center)
                + vertical_center;
            float horizontal_position = (float) -sin(angle) *
                (row - vertical_center) + cos(angle) * (col - horizontal_center)
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
                float interpolated = bilinearly_interpolate(top, bottom, left,
                    right, horizontal_position, vertical_position,
                    greyscale_in);
                output[row][col] = interpolated;
            }
        }
    }

    return output;
}