#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include "image.hpp"

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

class rgb_image: public image {
    public:
        rgb_image(int width, int height);

        rgb_image(const char *filename);
};

#endif  /* RGB_IMAGE_HPP */