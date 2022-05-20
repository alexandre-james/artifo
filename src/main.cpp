#include "image/conversion.hpp"
#include "features/histogram.hpp"
#include "modifier/modifier.hpp"
#include "modifier/filter.hpp"
#include "tools/saturation.hpp"
#include "tools/contrast.hpp"
#include "tools/manipulation.hpp"
#include "tools/sharpness.hpp"
#include "tools/edge.hpp"

#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid parameters\nformat: ./tifo <file_path>\n");
        return 1;
    }

    rgb_image *image = new rgb_image(argv[1]);

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

    int size = 3;
    float sigma = 0.84089642;

    if (access("output", F_OK))
        mkdir("output", 0777);
 
    rgb_image *result = gaussian(image, size, sigma);
    result->save("output/pure-gaussian.png");

    rgb_image *result2 = apply_channels(gaussian, image, size, sigma);
    result2->save("output/chan-gaussian.png");

    gray_image *gray = image->to_gray();
    gray_image *result3 = gaussian(gray, size, sigma);
    result3->save("output/gray-gaussian.png");

    gray_image *diff = multiply(difference_of_gaussian(gray, 2), 5);
    diff->save("output/diff.png");

    delete diff;

    delete result3;
    delete result2;
    delete gray;
    delete result;
    delete image;

    return 0;
}