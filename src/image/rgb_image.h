#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#include "image.h"

class rgb_image: public image {
    public:
        rgb_image(const char *filename);
};

#endif  /* RGB_IMAGE_H */