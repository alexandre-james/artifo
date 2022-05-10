#include "rgb_image.hpp"

rgb_image::rgb_image(int width, int height)
: image(width, height, 3) {}

rgb_image::rgb_image(const char *filename)
: image(filename, 3) {}