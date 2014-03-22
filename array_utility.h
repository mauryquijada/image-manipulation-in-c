/*

This header file provides utility operations that allow for easy manipulation
of image arrays.

This header file is a rewritten file based off of a version given by Prof. Ruye
Wang of Harvey Mudd's Department of Engineering (2013).

*/

#ifndef ARRAY_UTILITY_H
#define ARRAY_UTILITY_H

#include <stdio.h>

char fname[50];
FILE* fp;

double* alloc1dd (int n);
double** alloc2dd (int m, int n);

float* alloc1df (int n);
float** alloc2df (int m, int n);
float*** alloc3df (int l, int m, int n);
float**** alloc4df (int k, int l, int m, int n);

void dealloc2df (float** array, int m, int n);
void dealloc3df (float*** array, int l, int m, int n);
void dealloc4df (float**** array, int k, int l, int m, int n);

int* alloc1di (int n);
int** alloc2di (int m, int n);
int*** alloc3di (int l, int m, int n);

void dealloc2di (int** array, int m, int n);
void dealloc3di (int*** array, int l, int m, int n);

// This function prints an end of file error message and exits.
void eof_err ();

int getword (FILE* fp, char *word);

float*** read_color_image (char *fname, int *m, int *n);
float** read_bw_image (char *fname, int *m, int *n);

void write_color_image (char filename[], float*** image, int m, int n, int s);
void write_bw_image (char* filename, float** image, int m, int n, int s);

#endif
