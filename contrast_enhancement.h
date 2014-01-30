#ifndef CONTRAST_ENHANCEMENT_H
#define CONTRAST_ENHANCEMENT_H

float*** enhance_contrast (float*** input, int M_in, int N_in);

float*** linear_stretch (float*** input, int M_in, int N_in);

float*** min_max_stretch (float*** input, int M_in, int N_in, double cutoff);

#endif