#ifndef RGBA_IMAGE_H
#define RGBA_IMAGE_H

#include "image.h"

class rgba_image: public image {
    public:
        rgba_image(const char *filename);
};

#endif  /* RGBA_IMAGE_H */