#pragma once

#include <cstdint>

#define NB_LEVELS 256
#define MAX_LEVEL (NB_LEVELS - 1)

class image {
    public:
        int width, height, dim, length;

        uint8_t *pixels = nullptr;

        image(int width, int height, int dim);

        image(const char *filename, int dim);

        ~image();

        void save(const char *filename) const;
};