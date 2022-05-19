#include "filter.hpp"
#include "mask.hpp"
#include "../image/conversion.hpp"

template <typename image_type>
image_type *gaussian(image_type *input, int width, int height) {
    mask *kernel = new mask(width, height);
    for (int i = 0; i < width * height; i++) {
        kernel->values[i] = 1. / (width * height);
    }
    image_type *output = kernel->convolve(input);
    return output;
}

template <typename image_type>
image_type *sobel(image_type *input) {
    mask *dx_kernel = new mask({{-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}});
    mask *dy_kernel = dx_kernel->transpose();

    image_type *dx_output = dx_kernel->convolve(input);
    image_type *dy_output = dy_kernel->convolve(input);
    image_type *output = combine(dx_output, dy_output);

    delete dx_kernel;
    delete dy_kernel;
    delete dx_output;
    delete dy_output;

    return output;
}

template gray_image *gaussian(gray_image *input, int width, int height);
template rgb_image *gaussian(rgb_image *input, int width, int height);
template rgba_image *gaussian(rgba_image *input, int width, int height);
template hsv_image *gaussian(hsv_image *input, int width, int height);

template gray_image *sobel(gray_image *input);
template rgb_image *sobel(rgb_image *input);
template rgba_image *sobel(rgba_image *input);
template hsv_image *sobel(hsv_image *input);