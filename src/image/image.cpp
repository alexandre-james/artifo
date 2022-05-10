#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../lib/stb_image_write.h"

#include "image.hpp"

image::image(int width, int height, int channels)
: width(width), height(height), channels(channels) {
    length = width * height * channels;
    pixels = (uint8_t *) std::malloc(length);
}

image::image(const char *filename, int channels)
: channels(channels) {
    int bpp;
    if (stbi_info(filename, &width, &height, &bpp)) {
        pixels = stbi_load(filename, &width, &height, &bpp, channels);
        length = width * height * channels;
    }
    else {
        printf("error: can't open image\n");
    }
}

image::~image() {
    if (pixels != nullptr)
        free(pixels);
}

void image::save(const char *filename) const {
    stbi_write_png(filename, width, height, channels, pixels, width * channels);
}