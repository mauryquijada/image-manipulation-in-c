#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

// Helper function that returns the maximum value in an array of integers.
int max_value (int* array, int num_elements);

float** generate_density_histogram (float** input, int size, int M_in,
    int N_in);

float** generate_cumulative_histogram (float** img, int size, int M_in,
    int N_in);

#endif
