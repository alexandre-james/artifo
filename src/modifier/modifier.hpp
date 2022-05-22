#pragma once

#include "../features/histogram.hpp"
#include "../image/rgb_image.hpp"

template <typename image_type>
class modifier {
    public:
        image_type *input;
        float threshold;

        int min, max;

        modifier(image_type *input, float threshold = 0.6);
        ~modifier();

        template <typename lambda>
        image_type *apply(lambda function) {
            image_type* output = new image_type(input->width, input->height);
            for (int i = 0; i < output->length; i++) {
                output->pixels[i] = function(input->pixels[i]);
            }
            return output;
        }

        image_type *linear();
        image_type *log();
};