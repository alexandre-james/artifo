#include <cstdlib>

#include "modifier.hpp"
#include "../image/conversion.hpp"

template <typename image_type>
modifier<image_type>::modifier(image_type *input, float threshold)
: input(input), threshold(threshold) {
    histograms = (histogram *) malloc(sizeof(histogram) * input->dim);
    minimums = (int *) malloc(sizeof(int) * input->dim);
    maximums = (int *) malloc(sizeof(int) * input->dim);

    for (int i = 0; i < input->dim; i++) {
        channels[i] = get_channel(input, i);
        histograms[i] = gray_histogram(channels[i]);
        densest(histograms[i], threshold, minimums[i], maximums[i]);
    }
}

template <typename image_type>
modifier<image_type>::~modifier() {
    for (int i = 0; i < input->dim; i++) {
        free(channels[i]);
    }
    free(channels);
    free(histograms);
    free(minimums);
    free(maximums);
}

template <typename image_type>
image_type *modifier<image_type>::linear() {
    auto function = [=, *this] (int x, int nb) {
        if (x < minimums[nb])
            return 0;
        if (x > maximums[nb])
            return NB_LEVELS - 1;
        int a = NB_LEVELS / (maximums[nb] - minimums[nb]);
        return a * x - a * minimums[nb];
    };

    return apply(function);
}

template class modifier<gray_image>;
template class modifier<rgb_image>;
template class modifier<rgba_image>;