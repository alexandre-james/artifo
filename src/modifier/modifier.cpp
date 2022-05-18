#include <cstdlib>

#include "modifier.hpp"
#include "../image/conversion.hpp"

#include <cstdio>
#include <cmath>

template <typename image_type>
modifier<image_type>::modifier(image_type *input, float threshold)
: input(image_copy(input)), threshold(threshold) {
    channels = (gray_image **) malloc(sizeof(gray_image *) * input->dim);
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
    delete input;
    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
    }
    free(channels);
    free(histograms);
    free(minimums);
    free(maximums);
}

template <typename image_type>
image_type *modifier<image_type>::linear() {
    auto function = [this] (int x, int nb) {
        if (x < minimums[nb])
            return 0;
        if (x > maximums[nb])
            return MAX_LEVEL;
        float a = (float) MAX_LEVEL / (maximums[nb] - minimums[nb]);
        return (int) (a * x - a * minimums[nb]);
    };

    return apply(function);
}

template <typename image_type>
image_type *modifier<image_type>::log() {
    auto function = [this] (int x, int nb) {
        if (x == 0)
            return 0;
        else
            return (int) (std::log(x) / std::log(maximums[nb]) * maximums[nb]);
    };

    return apply(function);
}

template class modifier<gray_image>;
template class modifier<rgb_image>;
template class modifier<rgba_image>;