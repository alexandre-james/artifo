#include "manipulation.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>

// Apply a function to each channel of an image
template <typename image_type>
image_type *apply_channels(image_type *input, gray_image *(*function)(gray_image *)) {
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

template gray_image *apply_channels(gray_image *input, gray_image *(*function)(gray_image *));
template rgb_image *apply_channels(rgb_image *input, gray_image *(*function)(gray_image *));
template rgba_image *apply_channels(rgba_image *input, gray_image *(*function)(gray_image *));
template hsv_image *apply_channels(hsv_image *input, gray_image *(*function)(gray_image *));