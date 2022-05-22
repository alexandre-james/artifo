#include "mask.hpp"
#include "../image/conversion.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdio>

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

/* padded convolve: DO NOT DELETE, this might be useful
template <typename image_type>
image_type *mask::convolve(image_type *input) {
    int y_gap = height / 2;
    int x_gap = width / 2;
    image_type *output = new image_type(input->width - 2 * x_gap, input->height - 2 * y_gap);
    for (int y = 0; y < output->height; y++) {
        for (int x = 0; x < output->width * input->dim; x++) {
            float sum = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    sum += (float) values[i * width + j] * (float) input->pixels[(y + i) * input->width * input->dim + x + j];
                }
            }
            output->pixels[y * output->width * output->dim + x] = bound(sum);
        }
    }
    return output;
}*/

void mask::print_row(int i) {
    if (i != 0)
        printf(" ");
    printf("[");
    if (width < 15) {
        for (int j = 0; j < width; j++)
            printf(" %f", values[i * width + j]);
    }
    else {
        for (int j = 0; j < 3; j++)
            printf(" %f", values[i * width + j]);
        printf(" ...");
        for (int j = width - 3; j < width; j++)
            printf(" %f", values[i * width + j]);
    }
    printf("]");
    if (i != height - 1)
        printf("\n");
}

void mask::print() {
    printf("[");
    if (height < 15) {
        for (int i = 0; i < height; i++)
            print_row(i);
    }
    else {
        for (int i = 0; i < 3; i++)
            print_row(i);
        printf(" ...\n");
        for (int i = height - 3; i < height; i++)
            print_row(i);
    }
    printf("]\n");
}