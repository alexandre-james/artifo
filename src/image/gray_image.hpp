#ifndef GRAY_IMAGE_HPP
#define GRAY_IMAGE_HPP

#include "image.hpp"

class gray_image: public image {
    public:
        gray_image(int width, int height);

        gray_image(const char *filename);
};

#endif  /* GRAY_IMAGE_HPP */