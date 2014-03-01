#ifndef KERNEL_FILTER_H
#define KERNEL_FILTER_H

float** add (float** arrayOne, float** arrayTwo, int row, int col);
float** subtract (float** arrayOne, float** arrayTwo, int row, int col);
float** find_pixel_matrix (float** input, int M_in, int N_in,
    int row, int col, int size);
float convolve_matrices (float** array_one, float** array_two, int size);
float*** convolve (float*** input, int M_in, int N_in, float** kernel, int dim);

float*** lowpass_filter(float*** input, int M_in, int N_in);
float*** highpass_filter(float*** input, int M_in, int N_in);
float** lowpass_filter_3by3kernel();
float** highpass_filter_3by3kernel();

#endif
