#include "array_utility.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fname[50];
FILE* fp;

double* alloc1dd (int n)
{
    int i;
    double* array;
    if ((array = (double*) malloc(n * sizeof(double))) == NULL) {
        printf("Unable to allocate memory for 1D double array...\n");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        array[i] = 0.0;
    }

    return array;
}

double** alloc2dd (int m, int n)
{
    int i, j;
    double** array;
    if ((array = (double **) malloc(m * sizeof(double*))) == NULL) {
        printf("Unable to allocate memory for 2D float array...\n");
        exit(0);
    }

    for (i = 0; i < m; i++) {
        array[i] = alloc1dd(n);
    }

    return array;
}

float* alloc1df (int n)
{
    int i;
    float* array;
    if ((array = (float*) malloc(n * sizeof(float))) == NULL) {
        printf("Unable to allocate memory for 1D float array...\n");
        exit(0);
    }

    for (i = 0; i < n; i++) {
        array[i] = 0.0;
    }

    return array;
}

float** alloc2df (int m, int n)
{
    int i,j;
    float** array;
    if ((array = (float **) malloc(m * sizeof(float*))) == NULL) {
        printf("Unable to allocate memory for 2D float array...\n");
        exit(0);
    }

    for (i = 0; i < m; i++) {
        array[i] = alloc1df(n);
    }

    return array;
}

float*** alloc3df (int l, int m, int n)
{
    int i;
    float*** array;

    if ((array = (float ***) malloc(l * sizeof(float**))) == NULL) {
        printf("Unable to allocate memory for 3D float array...\n");
        exit(0);
    }

    for (i = 0; i < l; i++) {
        array[i] = alloc2df(m,n);
    }

    return array;
}

float**** alloc4df (int k, int l, int m, int n)
{
    int i;
    float**** array;

    if ((array = (float ****) malloc(k * sizeof(float***))) == NULL) {
        printf("Unable to allocate memory for 4D float array...\n");
        exit(0);
    }

    for (i = 0; i < k; i++) {
        array[i] = alloc3df(l,m,n);
    }

    return array;
}

void dealloc2df (float** array, int m, int n)
{
    int i;
    for (i = 0; i < m; i++) {
        free(array[i]);
    }

    free(array);
}

void dealloc3df (float*** array, int l, int m, int n)
{
    int i;
    for (i = 0; i < l; i++) {
        dealloc2df(array[i], m, n);
    }

    free(array);
}

void dealloc4df (float**** array, int k, int l, int m, int n)
{
    int i;
    for (i = 0; i < k; i++) {
        dealloc3df(array[i], l, m, n);
    }

    free(array);
}

int* alloc1di (int n)
{
    int i, *array;
    if ((array = (int*) malloc(n * sizeof(int))) == NULL) {
        printf("Unable to allocate memory for 1D int array...\n");
        exit(0);
    }

    for (i = 0; i < n; i++) {
        array[i] = 0.0;
    }

    return array;
}

int** alloc2di (int m, int n)
{
    int i;
    int** array;
    if ((array = (int**) malloc(m * sizeof(int*))) == NULL) {
        printf("Unable to allocate memory for 2D int array...\n");
        exit(0);
    }

    for (i = 0; i < m; i++) {
       array[i] = alloc1di(n);
    }

    return array;
}


int*** alloc3di (int l, int m, int n)
{
    int i;
    int*** array;
    if ( (array = (int ***) malloc(l * sizeof(int**)) )==NULL) {
        printf("Unable to allocate memory for 3D int array...\n");
        exit(0);
    }

    for (i = 0; i < l; i++) {
        array[i] = alloc2di(m, n);
    }

    return array;
}

void dealloc2di (int** array, int m, int n)
{
    int i;
    for (i = 0; i < m; i++) {
        free(array[i]);
    }

    free(array);
}

void dealloc3di (int*** array, int l, int m, int n)
{
    int i;
    for (i = 0; i < l; i++) {
        dealloc2di(array[i], m, n);
    }

    free(array);
}

// This function prints an end of file error message and exits.
void eof_err ()
{
    printf("Unexpected end of file, exiting. \n");
    exit(0);
}

int getword (FILE* fp, char *word)
{
    int i = 0, cha = ' ';
    short end = 0;

    do { // Eliminate White Space and comments (from # to end of line)
        cha = fgetc(fp);
        if (cha=='#') {
            do cha = fgetc(fp);
            while (!(cha == '\n'));
        }
    }
    while (isspace(cha) && (cha != EOF));

    if (cha == EOF) {
        return -1;
    } else { // get chars until a whitespace or End of File
        do {
            word[i++] = cha;
            cha = fgetc(fp);
        } // Get Single Word
        while (!(isspace(cha)) && (cha != EOF));
    }

    if (cha == EOF) {
        end = 1;  // if end of the file then we are done reading chars
    }

    word[i] = '\0';
    return end;
}


float*** read_color_image (char *fname, int *m, int *n)
{
    int c, i, j, k, Max;
    float*** img;
    char word[10];
    FILE* fp;
    char magic[4];

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Unable to open file: %s for reading, exiting.\n", fname);
        exit(0);
    }

    if (getword(fp,word) != 0) {
        eof_err();
    }

    strcpy(magic,word);

    if ((strcmp(magic,"P5") != 0) && (strcmp(magic,"P6") != 0)) {
        printf("\nBad file type, use raw grayscale (pgm) or raw color (ppm)");
        printf("file.\n");
        exit(0);
    }

    if (getword(fp,word) != 0) {
        eof_err();
    }
    *n = atoi(word);

    if (getword(fp,word) != 0) {
        eof_err();
    }
    *m = atoi(word);

    if (getword(fp,word) != 0) {
        eof_err();
    }
    Max = atoi(word);

    img = alloc3df(3,*m,*n);

    for (i=0; i<*m; i++) {
        for (j=0; j<*n; j++) {
            for (k=0; k<3; k++) {
                c = fgetc(fp);
                if (c==EOF) {
                    eof_err();
                }
               img[k][i][j]=c;
           }
        }
    }

    fclose(fp);

    return img;
}

float** read_bw_image (char *fname, int *m, int *n)
{
    int c, i, j, Max;
    float** img;
    char word[10];
    FILE* fp;
    char magic[4];

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Unable to open file: %s for reading, exiting.\n", fname);
        exit(0);
    }

    if (getword(fp,word) != 0) {
        eof_err();
    }

    strcpy(magic,word);

    if ((strcmp(magic, "P5") != 0) && (strcmp(magic, "P6") != 0)) {
        printf("\nBad file type, use raw grayscale (pgm) or raw color (ppm)");
        printf("file.\n");
        exit(0);
    }

    if (getword(fp, word) != 0) {
        eof_err();
    }
    *n = atoi(word);

    if (getword(fp, word) != 0) {
        eof_err();
    }
    *m = atoi(word);

    if (getword(fp, word) != 0) {
        eof_err();
    }
    Max = atoi(word);

    img = alloc2df(*m, *n);

    for (i = 0; i < *m; i++) {
        for (j = 0; j < *n; j++) {
            c = fgetc(fp);
            if (c == EOF) {
                eof_err();
            }
            img[i][j] = c;
        }
    }

    fclose(fp);

    return img;
}

void write_color_image (char filename[], float*** image, int m, int n, int s)
{
    int i, j, k, l;
    float v, min, max, ***Image;
    unsigned char w;
    FILE* fp;
    min = 9e9;
    max = -min;

    for (k = 0; k < 3; k++){
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                v = image[k][i][j];
                if (min > v) {
                    min = v;
                }

                if (max < v) {
                    max = v;
                }
            }
        }
    }

    v = 254.99 / (max - min);

    for (k=0; k<3; k++) {
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                image[k][i][j] = v * (image[k][i][j]-min);
            }
        }
    }

    printf("Write color image: min=%f, max=%f, v=%f\n", min,max,v);

    if ((fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Unable to open image %s for writing, exiting.\n",
            filename);
        exit(0);
    }

    fprintf(fp, "%s\n%d %d\n%d\n", "P6", s*n, s*m, 255);

    for (i = 0; i < m; i++) {
        for (k = 0; k < s; k++) {
            for (j = 0; j < n; j++) {
                for (l=0; l<s; l++) {
                    putc(w = image[0][i][j],fp);
                    putc(w = image[1][i][j],fp);
                    putc(w = image[2][i][j],fp);
                }
            }
        }
    }

    fclose(fp);
}

void write_bw_image (char* filename, float** image, int m, int n, int s)
{
    int i, j, k, l;
    float v, min, max;
    unsigned char w;
    FILE* fp;

    printf("\nWrite black/white image %s of size (%d, %d).\n",filename,m,n);

    min = 9e9;
    max = -min;

    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            v=image[i][j];
            if (min>v) {
                min=v;
            }
            if (max<v) {
                max=v;
            }
        }
    }

    v = 254.99 / (max - min);

    printf("Write image: min=%f, max=%f, v=%f\n", min,max,v);

    if ((fp = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Unable to open image %s for writing, exiting.\n",
            filename);
        exit(0);
    }

    fprintf(fp, "%s\n%d %d\n%d\n", "P5", s*n, s*m, 255);
    for (i=0; i<m; i++) {
        for (l=0; l<s; l++) {
            for (j=0; j<n; j++) {
                for (k=0; k<s; k++) {
                    putc(w = (image[i][j] - min) * v, fp);
                }
            }
        }
    }

    fclose(fp);
}