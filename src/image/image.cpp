#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../lib/stb_image_write.h"

#include "image.hpp"

image::image(int width, int height, int dim)
: width(width), height(height), dim(dim) {
    length = width * height * dim;
    pixels = (uint8_t *) std::malloc(length);
}

image::image(const char *filename, int dim)
: dim(dim) {
    int bpp;
    if (stbi_info(filename, &width, &height, &bpp)) {
        pixels = stbi_load(filename, &width, &height, &bpp, dim);
        length = width * height * dim;
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
    stbi_write_png(filename, width, height, dim, pixels, width * dim);
}