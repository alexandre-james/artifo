#include <stdio.h>

#include "image/conversion.hpp"
#include "features/histogram.hpp"

int main() {
    rgb_image *image = new rgb_image("input/image.png");

    gray_image *image2 = rgb_to_gray(image);

    histogram histogram = gray_histogram(image2);

    rgba_image *image3 = histogram_to_image(histogram);

    image3->save("test.png");

    delete image;
    delete image2;
    delete image3;
}