#include "rgb_image.hpp"

#include <cstring>

rgb_image::rgb_image(int width, int height)
: image(width, height, 3) {}

rgb_image::rgb_image(const char *filename)
: image(filename, 3) {}

rgb_image *rgb_image::copy() const {
    rgb_image *output = new rgb_image(width, height);
    memcpy(output->pixels, pixels, length);
    return output;
}

gray_image *rgb_image::to_gray() const {
    gray_image *output = new gray_image(width, height);
    for (int i = 0 ; i < output->length ; i++) {
        output->pixels[i] = 0.299 * pixels[3 * i]
        + 0.587 * pixels[3 * i + 1]
        + 0.114 * pixels[3 * i + 2];
    }
    return output;
}