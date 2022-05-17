#include <cstdlib>

#include "modifier.hpp"

template <typename image_type>
modifier<image_type>::modifier(image_type *input, float threshold)
: input(input), threshold(threshold) {
    histograms = (histogram *) malloc(sizeof(histogram) * input->dim);
    minimums = (int *) malloc(sizeof(int) * input->dim);
    maximums = (int *) malloc(sizeof(int) * input->dim);

    for (int i; i < input->dim; i++) {
        channels[i] = get_channel(input, i);
        histograms[i] = gray_histogram(channels[i]);
        densest(histograms[i], threshold, minimums[i], maximums[i]);
    }
}

template <typename image_type>
modifier<image_type>::~modifier() {
    for (int i = 0; i < input->nb_chan; i++) {
        free(channels[i]);
    }
    free(channels);
    free(histograms);
    free(minimums);
    free(maximums);
}

template <typename image_type, typename lambda>
image_type *modifier<image_type>::apply(lambda function) {
    image_type* output = new image_type(input->width, input->height);
    for (int i = 0; i < output->width * output->height; i++) {
        output->pixels[i] = function(input->pixels[i], i % input->nb_chan);
    }
    return output;
}

template <typename image_type>
image_type *modifier<image_type>::linear() {
    auto function = [] (int x, int nb) {
        if (x < minimums[nb])
            return 0;
        if (x > maximums[nb])
            return IMAGE_NB_LEVELS - 1;
        int a = IMAGE_NB_LEVELS / (maximums[nb] - minimums[nb]);
        return a * x - a * minimums[nb];
    };

    return apply(function);
}