#include <stdio.h>

#include "image/conversion.hpp"
#include "features/histogram.hpp"
#include "modifier/modifier.hpp"

int main() {
    rgb_image *image = new rgb_image("input/image.png");

    gray_image *image2 = rgb_to_gray(image);

    histogram histogram = gray_histogram(image2);

    rgba_image *image3 = histogram_to_image(histogram);

    modifier<rgb_image> *modifer = new modifier(image);

    rgb_image *image4 = modifer->linear();

    image4->save("test.png");

    delete image;
    delete image2;
    delete image3;
    delete image4;
    delete modifer;
}