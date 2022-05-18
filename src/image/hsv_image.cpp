#include "hsv_image.hpp"

#include <cstring>

hsv_image::hsv_image(int width, int height)
: image(width, height, 3) {}

hsv_image::hsv_image(const char *filename)
: image(filename, 3) {}

hsv_image *hsv_image::copy() const {
    hsv_image *output = new hsv_image(width, height);
    memcpy(output->pixels, pixels, length);
    return output;
}