#include <stdio.h>

#include "image/conversion.hpp"
#include "features/histogram.hpp"
#include "modifier/modifier.hpp"

int main() {
    rgb_image *image = new rgb_image("input/test.jpg");

    /*

    gray_image *blue = get_channel(image, BLUE_CHANNEL);

    modifier<gray_image> *modifer = new modifier(blue);

    rgba_image *hist = histogram_to_image(modifer->histograms[0]);

    gray_image *blue_linear = modifer->linear();

    rgb_image *result = set_channel(image, blue_linear, BLUE_CHANNEL);

    hist->save("hist.png");
    result->save("test-linear.png");
    blue->save("test-blue.png");
    blue_linear->save("test-blue_linear.png");

    delete hist;
    delete image;
    delete blue;
    delete modifer;
    delete blue_linear;
    delete result;*/

    hsv_image *hsv = rgb_to_hsv(image);
    hsv->save("hsv.png");

    rgb_image *result = hsv_to_rgb(hsv);
    result->save("result.png");

    delete result;
    delete image;
    delete hsv;
}