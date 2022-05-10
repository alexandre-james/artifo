#include "gray_image.hpp"

gray_image::gray_image(int width, int height)
: image(width, height, 1) {}

gray_image::gray_image(const char *filename)
: image(filename, 1) {}