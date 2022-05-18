#include "gray_image.hpp"

#include <cstring>

gray_image::gray_image(int width, int height)
: image(width, height, 1) {}

gray_image::gray_image(const char *filename)
: image(filename, 1) {}

gray_image *gray_image::copy() const {
    gray_image *output = new gray_image(width, height);
    memcpy(output->pixels, pixels, length);
    return output;
}

gray_image *gray_image::to_gray() const {
    return copy();
}