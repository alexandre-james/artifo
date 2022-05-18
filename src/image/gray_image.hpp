#ifndef GRAY_IMAGE_HPP
#define GRAY_IMAGE_HPP

#include "image.hpp"

class gray_image: public image {
    public:
        gray_image(int width, int height);

        gray_image(const char *filename);

        gray_image *copy() const;

        gray_image *to_gray() const;
};

#endif  /* GRAY_IMAGE_HPP */