#include "rgb_image.h"

rgb_image::rgb_image(const char *filename)
: image(filename, 3)
{}