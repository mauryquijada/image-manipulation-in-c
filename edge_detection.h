#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

float*** apply_Laplacian_of_Gaussian(float*** input, int M_in, int N_in,
	float threshold, int square_size);
float*** detect_edges(float*** input, int M_in, int N_in);

#endif