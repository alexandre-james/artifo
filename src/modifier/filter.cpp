#include "filter.hpp"
#include "mask.hpp"
#include "../image/gray_image.hpp"
#include "../image/rgb_image.hpp"
#include "../image/rgba_image.hpp"
#include "../image/hsv_image.hpp"

template <typename image_type>
image_type *gaussian(image_type *input) {
    mask *kernel = new mask(3, 3);
    for (int i = 0; i < kernel->width * kernel->height; i++) {
        kernel->values[i] = 1. / (kernel->width * kernel->height);
    }
    return kernel->convolve(input);
}

template gray_image *gaussian(gray_image *input);
template rgb_image *gaussian(rgb_image *input);
template rgba_image *gaussian(rgba_image *input);
template hsv_image *gaussian(hsv_image *input);