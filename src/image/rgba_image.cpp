#include "rgba_image.h"

rgba_image::rgba_image(const char *filename)
: image(filename, 4)
{}