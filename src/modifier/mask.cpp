#include "mask.hpp"
#include "../image/conversion.hpp"

#include <cassert>
#include <cstdlib>

mask::mask(int width, int height)
: width(width), height(height) {
    values = (float *) malloc(width * height * sizeof(float));
}

mask::mask(std::initializer_list<std::initializer_list<float>> init) {
    assert(init.size() > 0 && init.begin()->size() > 0);
    width = init.begin()->size();
    height = init.size();
    values = (float *) malloc(width * height * sizeof(float));

    int i = 0;
    for (std::initializer_list<float> list: init) {
        for (float value: list) {
            values[i++] = value;
        }
    }
}

mask::~mask() {
    free(values);
}

mask *mask::transpose() {
    mask *output = new mask(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            output->values[j * height + i] = values[i * width + j];
        }
    }
    return output;
}

template <typename image_type>
image_type *mask::convolve(image_type *input) {
    int y_gap = height / 2;
    int x_gap = width / 2;
    image_type *output = new image_type(input->width - (2 * x_gap), input->height - (2 * y_gap));
    for (int y = y_gap; y < input->height - y_gap; y++) {
        for (int x = x_gap; x < input->width * input->dim - x_gap; x++) {
            float sum = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    sum += (float) values[i * width + j] * (float) input->pixels[(y - y_gap + i) * input->width * input->dim + x - x_gap + j];
                }
            }
            output->pixels[(y - y_gap) * output->width * output->dim + x - x_gap] = bound(sum);
        }
    }
    return output;
}

template gray_image *mask::convolve(gray_image *input);
template rgb_image *mask::convolve(rgb_image *input);
template rgba_image *mask::convolve(rgba_image *input);
template hsv_image *mask::convolve(hsv_image *input);