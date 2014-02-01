image-manipulation-in-c
=======================

A C program that allows the user to input a PNG image through command line and select how they want to manipulate that image.

Using the provided Makefile, the user can compile using gcc/ clang and run the resulting "process" executable.
Running "./process" on the command line will allow the user to:
- Generate a density histogram for the image.
- Generate a cumulative histogram for the image.
- Improve the image's contrast.
- Resize an image's width and height by certain factors.
- Rotate an image by some angle (in degrees).
- Perform histogram equalization on the image.
- Rotate the image's hue.
- Increase the image's color saturation.
- Increase the image's intensity.
- Perform low-pass filtering on an image using a kernel.
- Perform high-pass filtering on an image using a kernel.
- Perform low-pass or high-pass filtering using a Fourier transform.
- Create a gradient image that accentuates changes in color based on the given image.
- Clean up an image using a median filter.
- Detect edges in an image.
