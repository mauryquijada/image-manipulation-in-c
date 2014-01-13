#include "bilinear_interpolation.h"

// Function that performs bilinear interpolation to determine the pixel
// value of a new pixel.
float bilinearly_interpolate (int top, int bottom, int left, int right,
    float horizontal_position, float vertical_position, float** input)
{
    // Determine the values of the corners.
    float top_left = input[top][left];
    float top_right = input[top][right];
    float bottom_left = input[bottom][left];
    float bottom_right = input[bottom][right];

    // Figure out "how far" the output pixel being considered is
    // between *_left and *_right.
    float horizontal_progress = horizontal_position -
        (float) left;
    float vertical_progress = vertical_position -
        (float) top;

    // Combine top_left and top_right into one large, horizontal
    // block.
    float top_block = top_left + horizontal_progress
        * (top_right - top_left);

    // Combine bottom_left and bottom_right into one large, horizontal
    // block.
    float bottom_block = bottom_left +
        horizontal_progress
        * (bottom_right - bottom_left);

    // Combine the top_block and bottom_block using vertical
    // interpolation and return as the resulting pixel.
    return top_block + vertical_progress * (bottom_block - top_block);
}