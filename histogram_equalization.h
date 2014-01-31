#ifndef HISTOGRAM_EQUALIZATION_H
#define HISTOGRAM_EQUALIZATION_H

float*** equalize (float*** input, int M_in, int N_in);
float*** apply_concave_equalization (float*** input, int M_in, int N_in);
float*** apply_convex_equalization (float*** input, int M_in, int N_in);

#endif