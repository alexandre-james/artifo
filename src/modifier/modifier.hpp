#ifndef MODIFIER_HPP
#define MODIFIER_HPP

#include "../features/histogram.hpp"

template <typename image_type>
class modifier {
    public:
        image_type *input;
        float threshold;

        gray_image **channels;
        histogram *histograms;
        int *minimums;
        int *maximums;

        modifier(image_type *input, float threshold = 0.6);
        ~modifier();

        template <typename image_type, typename lambda>
        image_type *apply(lambda function);

        image_type *linear();
        image_type *log();
};

#endif  /* MODIFIER_HPP */