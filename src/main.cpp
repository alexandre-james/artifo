#include <stdio.h>

#include "image/conversion.hpp"
#include "features/histogram.hpp"
#include "modifier/modifier.hpp"
#include "modifier/filter.hpp"
#include "tools/saturation.hpp"
#include "tools/contrast.hpp"
#include "tools/manipulation.hpp"

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

    rgb_image *result = gaussian(image, 10, 10);
    result->save("pure-gaussian.png");

    rgb_image *result2 = apply_channels(gaussian, image, 10, 10);
    result2->save("chan-gaussian.png");

    gray_image *gray = image->to_gray();
    gray_image *result3 = gaussian(gray, 10, 10);
    result3->save("gray-gaussian.png");

    delete gray;
    delete result;
    delete result2;
    delete result3;
    delete image;
}