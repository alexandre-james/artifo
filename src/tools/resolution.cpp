#include "resolution.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>
#include <cstdio>
#include <algorithm>

template <typename image_type>
image_type *rescale(image_type *input, int height, int width) {
    double ratio = (double) height / (double) input->height;
    width = input->width * ratio;
    
    long *sums = (long *) calloc(height * width * input->dim, sizeof(long));
    int *sizes = (int *) calloc(height * width * input->dim, sizeof(int));

    printf("prev len: %d\n", input->height * input->width * input->dim);

    printf("new len: %d\n", height * width * input->dim);

    // average
    for (int y = 0; y < input->height; y++) {
        for (int x = 0; x < input->width * input->dim; x++) {
            int y_pos = y * ratio;
            int x_pos = x * ratio;
            int pos = y_pos * width * input->dim + x_pos;
            if (pos < height * width * input->dim) {
                sums[pos] += input->pixels[y * input->width * input->dim + x];
                sizes[pos] += 1;
            }
        }
    }

    /* sampling
    int mx = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * input->dim; x++) {
            int y_pos = (double) y * ((double) input->height / height);
            int x_pos = (double) x * ((double) (input->width * input->dim) / width);
            int pos = y_pos * input->width * input->dim + x_pos;
            mx = std::max(mx, pos);
            if (pos < input->height * input->width * input->dim) {
                sums[y * width * input->dim + x] += input->pixels[pos];
                sizes[y * width * input->dim + x] += 1;
            }
        }
    }*/

    image_type *output = new image_type(width, height);

    int min = sizes[0];
    int max = sizes[0];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * output->dim; x++) {
            int pos = y * width * output->dim + x;
            min = std::min(min, sizes[pos]);
            max = std::max(max, sizes[pos]);
            output->pixels[pos] = bound((double) sums[pos] / sizes[pos]);
        }
    }

    printf("min: %d\n", min);
    printf("max: %d\n", max);

    free(sums);
    free(sizes);
    return output;
}

template gray_image *rescale(gray_image *, int, int);
template rgb_image *rescale(rgb_image *, int, int);
template rgba_image *rescale(rgba_image *, int, int);
template hsv_image *rescale(hsv_image *, int, int);