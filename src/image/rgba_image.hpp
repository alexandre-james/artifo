#pragma once

#include "image.hpp"

class rgba_image: public image {
    public:
        rgba_image(int width, int height);

        rgba_image(const char *filename);

        rgba_image *copy() const;
};