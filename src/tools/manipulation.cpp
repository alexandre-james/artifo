#include "manipulation.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>

// Apply a function to each channel of an image
template <typename image_type>
image_type *apply_channels(gray_image *(*function)(gray_image *), image_type *input) {
    gray_image **channels = get_channels(input);

    for (int i = 0; i < input->dim; i++) {
        gray_image *channel = function(channels[i]);
        delete channels[i];
        channels[i] = channel;
    }
    image_type *output = merge<image_type>(channels);

    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
    }
    free(channels);
    return output;
}

template <typename image_type>
image_type *apply_channels(gray_image *(*function)(gray_image *, int, int), image_type *input, int width, int height) {
    gray_image **channels = get_channels(input);

    for (int i = 0; i < input->dim; i++) {
        gray_image *channel = function(channels[i], width, height);
        delete channels[i];
        channels[i] = channel;
    }
    image_type *output = merge<image_type>(channels);

    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
    }
    free(channels);
    return output;
}

template gray_image *apply_channels(gray_image *(*function)(gray_image *), gray_image *input);
template rgb_image *apply_channels(gray_image *(*function)(gray_image *), rgb_image *input);
template rgba_image *apply_channels(gray_image *(*function)(gray_image *), rgba_image *input);
template hsv_image *apply_channels(gray_image *(*function)(gray_image *), hsv_image *input);

template gray_image *apply_channels(gray_image *(*function)(gray_image *, int, int), gray_image *input, int width, int height);
template rgb_image *apply_channels(gray_image *(*function)(gray_image *, int, int), rgb_image *input, int width, int height);
template rgba_image *apply_channels(gray_image *(*function)(gray_image *, int, int), rgba_image *input, int width, int height);
template hsv_image *apply_channels(gray_image *(*function)(gray_image *, int, int), hsv_image *input, int width, int height);