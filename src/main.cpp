#include "image/rgba_image.h"

#include <stdio.h>

int main() {
    rgba_image *image = new rgba_image("input/image.png");

    image->save("test.png");

    delete image;
}