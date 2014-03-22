#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

float* find_cross_array (float** input, int M_in, int N_in, int row, int col,
    int width, int height, int* array_size);
float* find_pixel_array (float** input, int M_in, int N_in,
    int row, int col, int size, int* array_size);
float*** median_filter (float*** input, int M_in, int N_in);
float*** square_median_filter (float*** input, int M_in, int N_in);
float*** cross_median_filter (float*** input, int M_in, int N_in);

#endif
