#pragma once

#include "../construct/point.hpp"

template <typename image_type>
point<int> bound_point(image_type *input, point<int> p);

template <typename image_type, typename lambda>
image_type *transform(image_type *input, lambda function) {
    image_type* output = new image_type(input->width, input->height);
    for (int i = 0; i < output->length; i++) {
        output->pixels[0] = 0;
    }
    for (int y = 0; y < output->height; y++) {
        for (int x = 0; x < output->width; x++) {
            point<int> p = bound_point(input, function(x, y));
            for (int i = 0; i < output->dim; i++) {
                output->pixels[y * output->width * output->dim + x * output->dim + i] = input->pixels[p.y * input->width * input->dim + p.x * input->dim + i];
            }
        }
    }
    return output;
}