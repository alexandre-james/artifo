#include "tv.hpp"
#include "../image/conversion.hpp"
#include "../modifier/transformation.hpp"

#include <cmath>

rgb_image *tv(rgb_image *input) {
    int width = 10;
    double size = (double) input->width / (width * 2 * M_PI);

    auto f = [size](int x, int y) {
        return point<int>(x + size * sin((double) x / size), y + size * sin((double) y / size));
    };

    return transform(input, f);
}