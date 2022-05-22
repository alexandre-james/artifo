#pragma once

#include "image.hpp"

#define H_CHANNEL 0
#define S_CHANNEL 1
#define V_CHANNEL 2

class hsv_image: public image {
    public:
        hsv_image(int width, int height);

        hsv_image(const char *filename);

        hsv_image *copy() const;
};