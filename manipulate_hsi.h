#ifndef MANIPULATE_HSI_H
#define MANIPULATE_HSI_H

void rgb_to_hsi (float R, float G, float B, float* H, float* S, float* I);
void hsi_to_rgb (float H, float S, float I, float* R, float* G, float* B);

float*** rotate_hue (float*** input, int M_in, int N_in);
float*** increase_saturation (float*** input, int M_in, int N_in);
float*** increase_intensity (float*** input, int M_in, int N_in);

#endif