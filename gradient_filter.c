#include "gradient_filter.h"
#include "array_utility.h"

float*** gradient_filter(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** roberts_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** sobel_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** prewitt_operator_3by3kernel(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** prewitt_operator_5by5kernel(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** vertical_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** horizontal_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}

float*** diagonal_compass_nw_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}


float*** diagonal_compass_ne_operator(float*** input, int M_in, int N_in)
{
    return alloc3df(3, M_in, N_in);
}