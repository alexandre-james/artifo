#include "manga.hpp"
#include "../image/conversion.hpp"
#include "../modifier/filter.hpp"
#include "../tools/contrast.hpp"
#include "../tools/edge.hpp"
#include "../tools/sharpness.hpp"

#include <cstdio>

rgb_image *manga(rgb_image *input) {
    rgb_image *contrasted = contrast(input, 0.8);
    gray_image *gray = contrasted->to_gray();
    gray_image *log = difference_of_gaussian(gray, 2);
    rgb_image *rgb = gray_to_rgb(log);
    rgb_image *output = contrast(rgb, 0);

    delete contrasted;
    delete gray;
    delete log;
    delete rgb;

    return output;
}