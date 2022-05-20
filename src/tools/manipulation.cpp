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

template <typename image_type, typename num_type1, typename num_type2>
image_type *apply_channels(gray_image *(*function)(gray_image *, num_type1, num_type2), 
image_type *input, num_type1 num1, num_type2 num2) {
    gray_image **channels = get_channels(input);

    for (int i = 0; i < input->dim; i++) {
        gray_image *channel = function(channels[i], num1, num2);
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

template gray_image *apply_channels(gray_image *(*f)(gray_image *), gray_image *);
template rgb_image *apply_channels(gray_image *(*f)(gray_image *), rgb_image *);
template rgba_image *apply_channels(gray_image *(*f)(gray_image *), rgba_image *);
template hsv_image *apply_channels(gray_image *(*f)(gray_image *), hsv_image *);

template gray_image *apply_channels(gray_image *(*f)(gray_image *, int, int), gray_image *, int, int);
template rgb_image *apply_channels(gray_image *(*f)(gray_image *, int, int), rgb_image *, int, int);
template rgba_image *apply_channels(gray_image *(*f)(gray_image *, int, int), rgba_image *, int, int);
template hsv_image *apply_channels(gray_image *(*f)(gray_image *, int, int), hsv_image *, int, int);

template gray_image *apply_channels(gray_image *(*f)(gray_image *, int, float), gray_image *, int, float);
template rgb_image *apply_channels(gray_image *(*f)(gray_image *, int, float), rgb_image *, int, float);
template rgba_image *apply_channels(gray_image *(*f)(gray_image *, int, float), rgba_image *, int, float);
template hsv_image *apply_channels(gray_image *(*f)(gray_image *, int, float), hsv_image *, int, float);