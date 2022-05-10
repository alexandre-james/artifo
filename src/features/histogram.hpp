#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include "../image/gray_image.hpp"
#include "../image/rgba_image.hpp"

typedef struct {
    unsigned int columns[NB_LEVELS];
} histogram;

histogram gray_histogram(const gray_image *image);

rgba_image *histogram_to_image(const histogram histogram, const char *color = "gray");

void densest(histogram histogram, float threshold, int &min, int &max);

#endif  /* HISTOGRAM_HPP */