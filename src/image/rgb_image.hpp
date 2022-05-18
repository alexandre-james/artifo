#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include "gray_image.hpp"

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

class rgb_image: public image {
    public:
        rgb_image(int width, int height);

        rgb_image(const char *filename);

        rgb_image *copy() const;

        gray_image *to_gray() const;
};

#endif  /* RGB_IMAGE_HPP */