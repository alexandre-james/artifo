#include "hsv_image.hpp"

hsv_image::hsv_image(int width, int height)
: image(width, height, 3) {}

hsv_image::hsv_image(const char *filename)
: image(filename, 3) {}