#include "manipulate_hsi.h"
#include "array_utility.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// This function is a rewritten version based off one given by Prof. Ruye
// Wang of Harvey Mudd's Department of Engineering (2013).
void rgb_to_hsi (float R, float G, float B, float* H, float* S, float* I)
{
    float r, g, b, w, i, min=1.e-6;
    *I = (i = R + G + B)/3.0;
    r = R / i;
    g = G / i;
    b = B / i;

    if (R==G && G==B) {
        *S = 0;
        *H = 0;
    } else {
        w = 0.5 * (R - G + R - B) / sqrt((R - G)*(R - G) + (R - B)*(G - B));

        if (w > 1) {
            w = 1;
        } else if(w < -1) {
            w = -1;
        }

        *H = acos(w);

        if (*H < 0) {
            printf("Error while converting to HSI (H < 0).");
            exit(1);
        }

        if (B > G) {
            *H = 2 * 3.14159 - *H;
        }

        if (r <= g && r <= b) {
            *S = 1 - 3 * r;
        }

        if (g <= r && g <= b) {
            *S = 1 - 3 * g;
        }

        if (b <= r && b <= g) {
            *S = 1 - 3 * b;
        }
    }
}

// This function is a rewritten version based off one given by Prof. Ruye
// Wang of Harvey Mudd's Department of Engineering (2013).
void hsi_to_rgb (float H, float S, float I, float* R, float* G, float* B)
{
    float r, g, b;

    if (S > 1) {
        S = 1;
    }

    if (I > 1) {
        I = 1;
    }

    if (S == 0) {
        *R = *G = *B = I;
    } else {
        if ((H >= 0) && (H <2*3.14159/3)) {
            b = (1 - S) / 3;
            r = (1 + S*cos(H) / cos(3.14159/3 - H)) / 3;
            g = 1 - r - b;
        } else if ((H >= 2*3.14159/3) && (H < 4*3.14159/3)) {
            H = H - 2*3.14159/3;
            r = (1 - S)/3;
            g = (1 + S*cos(H) / cos(3.14159/3-H)) / 3;
            b = 1 - r - g;
       } else if ((H >= 4*3.14159/3) && (H < 2*3.14159)) {
            H = H - 4*3.14159/3;
            g = (1 - S)/3;
            b = (1 + S*cos(H) / cos(3.14159/3 - H)) / 3;
            r = 1 - b - g;
        } else {
            printf("\nError: H is out of range at %f deg.\n", H*180 / 3.14159);
            exit(1);
        }

        if (r < 0 || g < 0 || b < 0) {
            printf("Error: Given invalid R, G, B values (%f, %f, %f).", r , g,
                b);
            exit(1);
        }

        if (r < 0) {
            r = 0;
        }
        if (g < 0) {
            g = 0;
        }
        if (b < 0) {
            b = 0;
        }

        *R = 3 * I * r;
        *G = 3 *I * g;
        *B = 3 * I * b;

        if (*R > 1) {
            *R=1;
        }
        if (*G > 1) {
            *G=1;
        }
        if (*B > 1) {
            *B=1;
        }
    }
}

float*** rotate_hue (float*** input, int M_in, int N_in)
{
    // Prompt the user.
    float degrees;
    printf("By how many degrees do you want to rotate the hue (a number less");
    printf(" than 360 degrees)?\n");
    scanf("%f", &degrees);

    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Loop through all of the pixels and modify them in one fell swoop.
    int i, j;
    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            // Convert the incoming color image into HSI coordinates.
            float h, s, k, r, g, b;
            rgb_to_hsi(input[0][i][j] / 255,
                input[1][i][j] / 255,
                input[2][i][j] / 255,
                &h, &s, &k);

            // Rotate the hue by however many degrees (convert to radians).
            h += degrees * (3.14159/180);

            // Ensure that our hue is below 2pi.
            if (h > 6.28) {
                h -= 6.28;
            }

            // Convert the HSI coordinates back into a color image.
            hsi_to_rgb(h, s, k, &r, &g, &b);

            output[0][i][j] = r * 255;
            output[1][i][j] = g * 255;
            output[2][i][j] = b * 255;
        }
    }

    return output;
}

float*** increase_saturation (float*** input, int M_in, int N_in)
{
    // Prompt the user.
    float saturation;
    printf("By what factor do you want to increase the saturation?\n");
    scanf("%f", &saturation);

    // Declare output.
    float*** output = alloc3df(3, M_in, N_in);

    // Loop through all of the pixels and modify them in one fell swoop.
    int i, j;
    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            // Convert the incoming color image into HSI coordinates.
            float h, s, k, r, g, b;
            rgb_to_hsi(input[0][i][j] / 255,
                input[1][i][j] / 255,
                input[2][i][j] / 255,
                &h, &s, &k);

            // Rotate the hue by 90 degrees, as required.
            s *= saturation;

            // Ensure that saturation is below 1.
            if (s > 1.0) {
                s = 1.0;
            }

            // Convert the HSI coordinates back into a color image.
            hsi_to_rgb(h, s, k, &r, &g, &b);

            output[0][i][j] = r * 255;
            output[1][i][j] = g * 255;
            output[2][i][j] = b * 255;
        }
    }

    return output;
}

float*** increase_intensity (float*** input, int M_in, int N_in)
{
    // Declare necessary variables.
    int i, j;
    float*** output = alloc3df(3, M_in, N_in);
    float* intensity_distribution = alloc1df(100);
    float intensity_density = (float) 1.0 / M_in / N_in;

    // Loop through all of the pixels in the image and find the lowest
    // and highest values for saturation when converted.
    float min_intensity = 1, max_intensity = 0;
    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            // Convert the incoming color image into HSI coordinates.
            float h, s, k;
            rgb_to_hsi(input[0][i][j] / 255,
                input[1][i][j] / 255,
                input[2][i][j] / 255,
                &h, &s, &k);

            // Weird bug that happens when you passed in an image already
            // converted from RGB -> HSI -> RGB where the H is greater
            // than 6.28. Add this check to make sure that doesn't happen.
            if (h > 6.28) {
                h = 6.28;
            }

            output[0][i][j] = h;
            output[1][i][j] = s;
            output[2][i][j] = k;

            intensity_distribution[(int) (k + 0.5) * 100] += intensity_density;

            // Find the minimum and maximum intensity
            if (k < min_intensity) {
                min_intensity = floorf(k * 100) / 100;
            } else if (k > max_intensity) {
                max_intensity = floorf(k * 100) / 100;
            }
        }
    }

    // Find the cutoff point.
    float w = 0;
    while (w < 0.03) {
        w += intensity_distribution[(int) (min_intensity + 0.5) * 100];
        min_intensity += 0.1;
    }

    w = 0;
    while (w < 0.03) {
        w += intensity_distribution[(int) (max_intensity + 0.5) * 100];
        max_intensity -= 0.1;
    }

    // Loop through the image pixels again and linearly stretch the intensity.
    for (i = 0; i < M_in; i++) {
        for (j = 0; j < N_in; j++) {
            float r, g, b;
            // Linearly stretech the altered image.
            if (output[2][i][j] < min_intensity) {
                output[2][i][j] = 0.0;
            } else if (output[2][i][j] > max_intensity) {
                output[2][i][j] = 1.0;
            } else {
                // Create the resulting saturation based on a linear scaling
                // factor that takes into account the min and max.
                output[2][i][j] = ((output[2][i][j] - min_intensity) /
                    (max_intensity - min_intensity));
            }

            // Convert the HSI coordinates back into a color image.
            hsi_to_rgb(output[0][i][j],
                output[1][i][j],
                output[2][i][j], &r, &g, &b);

            output[0][i][j] = r * 255;
            output[1][i][j] = g * 255;
            output[2][i][j] = b * 255;
        }
    }

    return output;
}
