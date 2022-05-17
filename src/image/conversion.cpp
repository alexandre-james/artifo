#include "conversion.hpp"

gray_image *rgb_to_gray(const rgb_image *input) {
    gray_image *output = new gray_image(input->width, input->height);
    for (int i = 0 ; i < output->length ; i++) {
        output->pixels[i] = 0.299 * input->pixels[3 * i]
        + 0.587 * input->pixels[3 * i + 1]
        + 0.114 * input->pixels[3 * i + 2];
    }
    return output;
}

rgb_image *gray_to_rgb(const gray_image *input) {
    rgb_image *output = new rgb_image(input->width, input->height);

    for (int i = 0 ; i < input->length ; i++) {
        output->pixels[3 * i] = input->pixels[i];
        output->pixels[3 * i + 1] = input->pixels[i];
        output->pixels[3 * i + 2] = input->pixels[i];
    }
    return output;
}

template <typename image_type>
gray_image *get_channel(image_type *input, const int nb) {
    if (nb >= input->dim)
        return nullptr;

    gray_image *output = new gray_image(input->width, input->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = input->pixels[input->dim * i + nb];
    }
    return output;
}

template gray_image* get_channel<gray_image>(gray_image *input, const int nb);
template gray_image* get_channel<rgb_image>(rgb_image *input, const int nb);
template gray_image* get_channel<rgba_image>(rgba_image *input, const int nb);