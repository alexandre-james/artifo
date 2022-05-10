#ifndef RGBA_IMAGE_HPP
#define RGBA_IMAGE_HPP

#include "image.hpp"

class rgba_image: public image {
    public:
        rgba_image(int width, int height);

        rgba_image(const char *filename);
};

#endif  /* RGBA_IMAGE_HPP */