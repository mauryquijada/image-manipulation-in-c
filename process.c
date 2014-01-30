#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_utility.h"
#include "rotate.h"
#include "resize.h"
#include "histograms.h"
#include "lodepng.h"

float*** png_to_ppm (unsigned char* image, unsigned width, unsigned height)
{
	float*** img = alloc3df(3, height, width);

  	int i, j;
  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			img[0][i][j] = image[3 * i * width + 3 * j + 0]; // Red.
		    img[1][i][j] = image[3 * i * width + 3 * j + 1]; // Green.
		    img[2][i][j] = image[3 * i * width + 3 * j + 2]; // Blue.
  		}
  	}

  	return img;
}
unsigned char* ppm_to_png (float*** image, unsigned width, unsigned height)
{
	unsigned char* img = (unsigned char*) malloc(3 * width * height *
		sizeof(unsigned char));

  	int i, j;
  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			img[3 * i * width + 3 * j + 0] = image[0][i][j]; // Red.
		    img[3 * i * width + 3 * j + 1] = image[1][i][j]; // Green.
		    img[3 * i * width + 3 * j + 2] = image[2][i][j]; // Blue.
  		}
  	}

  	return img;
}

int main ()
{
	int action = 1;

	char filename[256];
	char saved_filename[256];

  	printf("Type in the name of the PNG file you would like to process.\n");
  	scanf("%s", filename);

  	setbuf(stdout, NULL);

  	// Load the PNG using LodePNG library.
  	printf("Processing the file...\n\n\n");
  	unsigned error;
 	unsigned char* image;
  	unsigned width, height;

  	error = lodepng_decode24_file(&image, &width, &height, filename);
  	if (error) {
  		printf("Error (%u) loading file: %s\n", error, lodepng_error_text(error));
  		exit(0);
  	}

	// Then use array to load into a three-dimensional array of R, G, and B values.
  	float*** input = png_to_ppm(image, width, height);
  	free(image);

    int i, j;
    int output_height, output_width;
	float*** output = (float ***) malloc(3 * sizeof(float**));

  	// Begin coding the user prompt menu.
  	while (action > 0) {
  		printf("Select how you would like to process this image: \n");
	  	printf("1) Generate a density histogram for the image.\n");
	  	printf("2) Generate a cumulative histogram for the image.\n");
	  	printf("3) Improve the image's contrast.\n");
	  	printf("4) Resize an image's width and height by certain factors.\n");
	  	printf("5) Rotate an image by some angle (in degrees).\n");
	  	printf("6) Perform histogram equalization on the image.\n");
	  	printf("7) Rotate the image's hue.\n");
	  	printf("8) Increase the intensity of the image.\n");
	  	printf("9) Increase the color saturation of the image.\n");
	  	printf("10) Perform low-pass filtering on an image using a kernel.\n");
	  	printf("11) Perform high-pass filtering on an image using a kernel.\n");
	  	printf("12) Perform low-pass or high-pass filtering us a Fourier");
	  	printf("transform.\n");
	  	printf("13) Create a gradient image that accentuates changes in color");
	  	printf("based on the given image.\n");
	  	printf("14) Clean up an image using a median filter.\n");
	  	printf("15) Detect edges in an image.\n");


	  	printf("Type in the number of the action you're interested in ");
	  	printf("(-1 to exit): ");
	  	scanf("%d", &action);
	  	printf("------------------------------------------------------\n\n\n");

	  	// Act according to what the user selected.
	  	switch (action) {
	  		case 1:
	  			output_height = output_width = 256;
	  			for (i = 0; i < 3; i++) {
	  				output[i] = generate_density_histogram(input[i],
	  					output_height, height, width);
	  			}

	  			strncpy(saved_filename, filename, 256);
	  			saved_filename[strlen(saved_filename) - 4] = 0;
	  			strcat(saved_filename, "_density_histogram.png");
	  			break;
	  		case 2:
	  			output_height = output_width = 256;
	  			for (i = 0; i < 3; i++) {
	  				output[i] = generate_cumulative_histogram(input[i],
	  					output_height, height, width);
	  			}

	  			strncpy(saved_filename, filename, 256);
	  			saved_filename[strlen(saved_filename) - 4] = 0;
	  			strcat(saved_filename, "_cumu_histogram.png");
	  			break;
	  		case 3:
	  			break;
	  		case 4:
	  			output_height = height;
	  			output_width = width;
	  			 output = resize(input, height, width, &output_height,
	  			 	&output_width);

	  			strncpy(saved_filename, filename, 256);
	  			saved_filename[strlen(saved_filename) - 4] = 0;
	  			strcat(saved_filename, "_resized.png");
	  			break;
	  		case 5:
	  			output_height = height;
	  			output_width = width;
	  			output = rotate(input, height, width);

	  			strncpy(saved_filename, filename, 256);
	  			saved_filename[strlen(saved_filename) - 4] = 0;
	  			strcat(saved_filename, "_rotated.png");
	  			break;
	  		case 6:
	  			break;
	  		case 7:
	  			break;
	  		case 8:
	  			break;
	  		case 9:
	  			break;
	  		case 10:
	  			break;
	  		case 11:
	  			break;
	  		case 12:
	  			break;
	  		case 13:
	  			break;
	  		case 14:
	  			break;
	  		case 15:
	  			break;
	  		default:
	  			break;
	  	}

	  	if (action > 0) {
		  	// Save the file and indicate what the file was saved as.
		  	unsigned char* output_png = ppm_to_png(output, output_width,
		  		output_height);
			error = lodepng_encode24_file(saved_filename, output_png,
				output_width, output_height);
			if (error) {
		  		printf("Error (%u) saving file: %s\n\n\n", error, lodepng_error_text(error));
		  	} else {
		  		printf("The file was successfully saved as %s.\n\n\n", saved_filename);
		  	}
	  	}
  	}

  	dealloc3df(input, 3, height, width);
}