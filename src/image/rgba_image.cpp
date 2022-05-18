#include "rgba_image.hpp"

#include <cstring>

rgba_image::rgba_image(int width, int height)
: image(width, height, 4) {}

rgba_image::rgba_image(const char *filename)
: image(filename, 4) {}

rgba_image *rgba_image::copy() const {
    rgba_image *output = new rgba_image(width, height);
    memcpy(output->pixels, pixels, length);
    return output;
}