#ifndef HSV_IMAGE_HPP
#define HSV_IMAGE_HPP

#include "image.hpp"

class hsv_image: public image {
    public:
        hsv_image(int width, int height);

        hsv_image(const char *filename);
};

#endif  /* HSV_IMAGE_HPP */