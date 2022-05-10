#ifndef RGB_IMAGE_HPP
#define RGB_IMAGE_HPP

#include "image.hpp"

class rgb_image: public image {
    public:
        rgb_image(int width, int height);

        rgb_image(const char *filename);
};

#endif  /* RGB_IMAGE_HPP */