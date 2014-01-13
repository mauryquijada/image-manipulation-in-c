#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_utility.h"
#include "rotate.h"
#include "resize.h"
#include "histograms.h"
#include "lodepng.h"

int main ()
{
	int action = 0;

	char* filename;
  	printf("Type in the name of the PNG file you would like to process.\n");
  	scanf("%s", filename);

  	// Load the PNG using LodePNG library.
  	// Ignoring Alpha values for now.
  	printf("Processing the file...\n\n\n");
  	unsigned error;
 	unsigned char* image;
  	unsigned width, height;

  	error = lodepng_decode32_file(&image, &width, &height, filename);
  	if (error) {
  		printf("Error (%u) loading file: %s\n", error, lodepng_error_text(error));
  	}

	// Then use array to load into a three-dimensional array of R, G, and B values.
  	float*** img = alloc3df(3, height, width);

  	int i, j;
  	int r, g, b, a;
  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			img[0][i][j] = image[4 * i * width + 4 * j + 0]; // Red.
		    img[1][i][j] = image[4 * i * width + 4 * j + 1]; // Green.
		    img[2][i][j] = image[4 * i * width + 4 * j + 2]; // Blue.
		    // image[4 * i * width + 4 * j + 3]; is used to access alpha.
  		}
  	}

  	while (action > -1) {
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
	  	printf("based on input.\n");
	  	printf("14) Clean up an image using a median filter.\n");
	  	printf("15) Detect edges in an image.\n");


	  	printf("Type in the number of the action you're interested in (-1 to exit): ");
	  	scanf("%d", &action);
	  	printf("\n\n\n");
  	}


  	write_color_image("blah.ppm", img, height, width, 1);

  	dealloc3df(img, 3, height, width);
}