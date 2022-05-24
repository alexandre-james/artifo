#include "edge.hpp"
#include "manipulation.hpp"
#include "../image/conversion.hpp"
#include "../modifier/filter.hpp"

#include <cmath>
#include <cstdio>

// DoG (*ouaf*)
template <typename image_type>
image_type *difference_of_gaussian(image_type *input, int size) {
    float sigma = (size - 1) * 0.3 + 0.8;
    float sigma1 = sigma / std::sqrt(2);
    float sigma2 = sigma * std::sqrt(2);
    image_type *gauss1 = apply_channels(gaussian, input, size, sigma1);
    image_type *gauss2 = apply_channels(gaussian, input, 2 + size, sigma2);
    image_type *output = substract(gauss1, gauss2);

    delete gauss1;
    delete gauss2;

    return output;
}

template gray_image *difference_of_gaussian(gray_image *, int);
template rgb_image *difference_of_gaussian(rgb_image *, int);
template rgba_image *difference_of_gaussian(rgba_image *, int);
template hsv_image *difference_of_gaussian(hsv_image *, int);