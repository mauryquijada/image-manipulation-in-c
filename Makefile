# Constants
OBJECTS = array_utility.o bilinear_interpolation.o fourier_filter.o \
	frequency_filter.o gradient_filter.o histogram_equalization.o \
	histograms.o manipulate_hsi.o median_filter.o process.o resize.o \
	rotate.o

all:	process

clean:
	rm -rf *.0 *.dSYM process

process: $(OBJECTS)
	gcc -lm -g -o process $(OBJECTS)


array_utility.o: array_utility.c array_utility.h
bilinear_interpolation.o: bilinear_interpolation.c \
  bilinear_interpolation.h
fourier_filter.o: fourier_filter.c
frequency_filter.o: frequency_filter.c
gradient_filter.o: gradient_filter.c
histogram_equalization.o: histogram_equalization.c
histograms.o: histograms.c histograms.h
manipulate_hsi.o: manipulate_hsi.c
median_filter.o: median_filter.c
process.o: process.c array_utility.h rotate.h bilinear_interpolation.h \
  resize.h histograms.h
resize.o: resize.c resize.h bilinear_interpolation.h
rotate.o: rotate.c rotate.h bilinear_interpolation.h

