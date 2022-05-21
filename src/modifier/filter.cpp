#include "filter.hpp"
#include "convolution.hpp"
#include "../image/conversion.hpp"

#include <cmath>
#include <cstdio>

template <typename image_type>
image_type *average(image_type *input, int width, int height) {
    mask *kernel = new mask(width, height);
    for (int i = 0; i < width * height; i++) {
        kernel->values[i] = 1. / (width * height);
    }
    image_type *output = convolve(input, kernel);
    delete kernel;
    return output;
}

template <typename image_type>
image_type *gaussian(image_type *input, int size, float sigma) {
    mask *kernel = new mask(size * 2 + 1, size * 2 + 1);
    for (int y = -size; y <= size; y++) {
        for (int x = -size; x <= size; x++) {
            kernel->values[(y + size) * kernel->width + x + size] = 1 / (2 * M_PI * sigma * sigma) * exp(-(x * x + y * y) / (2 * sigma * sigma));
        }
    }
    image_type *output = convolve(input, kernel);
    delete kernel;
    return output;
}

template <typename image_type>
image_type *sobel(image_type *input) {
    mask *dx_kernel = new mask({{-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}});

    mask *dy_kernel = dx_kernel->transpose();

    image_type *dx_output = convolve(input, dx_kernel);
    image_type *dy_output = convolve(input, dy_kernel);
    image_type *output = add(dx_output, dy_output);

    delete dx_kernel;
    delete dy_kernel;
    delete dx_output;
    delete dy_output;

    return output;
}

template <typename image_type>
image_type *laplacian(image_type *input) {
    mask *kernel = new mask({{0, -1, 0},
                            {-1, 4, -1},
                            {0, -1, 0}});

    image_type *output = convolve(input, kernel);
    delete kernel;

    return output;
}

template <typename image_type>
image_type *laplacian_sharp(image_type *input) {
    mask *kernel = new mask({{0, -1, 0},
                            {-1, 5, -1},
                            {0, -1, 0}});

    image_type *output = convolve(input, kernel);
    delete kernel;

    return output;
}

template <typename image_type>
image_type *laplacian_of_gaussian(image_type *input, int size, float sigma) {
    mask *kernel = new mask(size * 2 + 1, size * 2 + 1);
    for (int y = -size; y <= size; y++) {
        for (int x = -size; x <= size; x++) {
            kernel->values[(y + size) * kernel->width + x + size] = - 480 / (M_PI * std::pow(sigma, 4)) * (1 - (x * x + y * y) / (2 * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
        }
    }
    image_type *output = convolve(input, kernel);
    delete kernel;
    return output;
}

template gray_image *average(gray_image *, int, int);
template rgb_image *average(rgb_image *, int, int);
template rgba_image *average(rgba_image *, int, int);
template hsv_image *average(hsv_image *, int, int);

template gray_image *gaussian(gray_image *, int, float);
template rgb_image *gaussian(rgb_image *, int, float);
template rgba_image *gaussian(rgba_image *, int, float);
template hsv_image *gaussian(hsv_image *, int, float);

template gray_image *sobel(gray_image *);
template rgb_image *sobel(rgb_image *);
template rgba_image *sobel(rgba_image *);
template hsv_image *sobel(hsv_image *);

template gray_image *laplacian(gray_image *);
template rgb_image *laplacian(rgb_image *);
template rgba_image *laplacian(rgba_image *);
template hsv_image *laplacian(hsv_image *);

template gray_image *laplacian_sharp(gray_image *);
template rgb_image *laplacian_sharp(rgb_image *);
template rgba_image *laplacian_sharp(rgba_image *);
template hsv_image *laplacian_sharp(hsv_image *);

template gray_image *laplacian_of_gaussian(gray_image *, int, float);
template rgb_image *laplacian_of_gaussian(rgb_image *, int, float);
template rgba_image *laplacian_of_gaussian(rgba_image *, int, float);
template hsv_image *laplacian_of_gaussian(hsv_image *, int, float);