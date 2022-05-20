#include "sharpness.hpp"

#include "manipulation.hpp"
#include "../modifier/filter.hpp"
#include "../image/conversion.hpp"

template <typename image_type>
image_type *high_boost(image_type *input) {
    int size = 4;
    float sigma = size / 3;
    image_type *gauss = apply_channels(gaussian, input, size, sigma);
    image_type *diff = substract(gauss, input);
    image_type *output = add(input, diff);

    delete gauss;
    delete diff;

    return output;
}

template gray_image *high_boost(gray_image *);
template rgb_image *high_boost(rgb_image *);
template rgba_image *high_boost(rgba_image *);
template hsv_image *high_boost(hsv_image *);