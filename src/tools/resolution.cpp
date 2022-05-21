#include "resolution.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>
#include <cstdio>
#include <algorithm>

template <typename image_type>
void extract(image_type *input, long *sums, int *sizes, int height, int is_average) {
    double y_ratio = (double) height / input->height;
    int width = input->width * y_ratio;
    double x_ratio = (double) width / input->width;
    
    // average mode
    if (is_average) {
        for (int y = 0; y < input->height; y++) {
            for (int x = 0; x < input->width * input->dim; x++) {
                int y_pos = y * y_ratio;
                int x_pos = x * x_ratio;
                int pos = y_pos * width * input->dim + x_pos;
                if (pos < height * width * input->dim) {
                    sums[pos] += input->pixels[y * input->width * input->dim + x];
                    sizes[pos] += 1;
                }
            }
        }
    }
    // sampling mode
    else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width * input->dim; x++) {
                int y_pos = (double) y * ((double) input->height / height);
                int x_pos = (double) x * ((double) input->height / height);
                int pos = y_pos * input->width * input->dim + x_pos * input->dim;
                if (pos < input->height * input->width * input->dim) {
                    sums[y * width * input->dim + x] += input->pixels[pos];
                    sizes[y * width * input->dim + x] += 1;
                }
            }
        }
    }
}

template <typename image_type>
image_type *rescale(image_type *input, int height, int is_average) {
    double ratio = (double) height / (double) input->height;
    int width = input->width * ratio;
    
    long *sums = (long *) calloc(height * width * input->dim, sizeof(long));
    int *sizes = (int *) calloc(height * width * input->dim, sizeof(int));

    extract(input, sums, sizes, height, is_average);

    image_type *output = new image_type(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * output->dim; x++) {
            int pos = y * width * output->dim + x;
            output->pixels[pos] = bound((double) sums[pos] / sizes[pos]);
        }
    }

    free(sums);
    free(sizes);
    return output;
}

template <typename image_type>
image_type *pixelize(image_type *input, int height, int is_average) {
    double y_ratio = (double) height / input->height;
    int width = input->width * y_ratio;
    double x_ratio = (double) width / input->width;
    
    long *sums = (long *) calloc(height * width * input->dim, sizeof(long));
    int *sizes = (int *) calloc(height * width * input->dim, sizeof(int));

    extract(input, sums, sizes, height, is_average);

    image_type *output = new image_type(input->width, input->height);

    for (int y = 0; y < output->height; y++) {
        for (int x = 0; x < output->width * output->dim; x++) {
            int y_pos = y * y_ratio;
            int x_pos = x * x_ratio;
            int pos = y_pos * width * output->dim + x_pos;
            output->pixels[y * output->width * output->dim + x] = bound((double) sums[pos] / sizes[pos]);
        }
    }

    free(sums);
    free(sizes);
    return output;
}

template gray_image *rescale(gray_image *, int, int);
template rgb_image *rescale(rgb_image *, int, int);
template rgba_image *rescale(rgba_image *, int, int);
template hsv_image *rescale(hsv_image *, int, int);

template gray_image *pixelize(gray_image *, int, int);
template rgb_image *pixelize(rgb_image *, int, int);
template rgba_image *pixelize(rgba_image *, int, int);
template hsv_image *pixelize(hsv_image *, int, int);