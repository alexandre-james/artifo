#include <cstdlib>

#include "modifier.hpp"
#include "../image/conversion.hpp"

#include <cstdio>
#include <cmath>

template <typename image_type>
modifier<image_type>::modifier(image_type *input, float threshold)
: input(image_copy(input)), threshold(threshold) {
    gray_image *gray = input->to_gray();
    densest(gray_histogram(gray), threshold, min, max);
    delete gray;
}

template <typename image_type>
modifier<image_type>::~modifier() {
    delete input;
}

template <typename image_type>
image_type *modifier<image_type>::linear() {
    auto function = [this] (int x) {
        if (x < min)
            return 0;
        if (x > max)
            return MAX_LEVEL;
        float a = (float) MAX_LEVEL / (max - min);
        return (int) (a * x - a * min);
    };

    return apply(function);
}

template <typename image_type>
image_type *modifier<image_type>::log() {
    auto function = [this] (int x) {
        if (x == 0)
            return 0;
        else
            return (int) (std::log(x) / std::log(max) * max);
    };

    return apply(function);
}

template class modifier<gray_image>;
template class modifier<rgb_image>;