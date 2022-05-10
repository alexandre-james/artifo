#include "rgba_image.hpp"

rgba_image::rgba_image(int width, int height)
: image(width, height, 4) {}

rgba_image::rgba_image(const char *filename)
: image(filename, 4) {}