#ifndef BILINEAR_INTERPOLATION_H
#define BILINEAR_INTERPOLATION_H

// Function that performs bilinear interpolation to determine the pixel
// value of a new pixel.
float bilinearly_interpolate (int top, int bottom, int left, int right,
    float horizontal_position, float vertical_position, float** input);

#endif
