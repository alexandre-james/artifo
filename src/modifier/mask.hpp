#pragma once

#include <initializer_list>

class mask {
    public:
        int width, height;
        float *values;

        mask(int width, int height);
        mask(std::initializer_list<std::initializer_list<float>> init);
        ~mask();

        mask *transpose();

        template <typename image_type>
        image_type *convolve(image_type *image);
};