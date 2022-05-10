#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>

#define NB_LEVELS 256
#define MAX_LEVEL (NB_LEVELS - 1)

class image {
    public:
        int width, height, channels, length;

        uint8_t *pixels = nullptr;

        image(int width, int height, int channels);

        image(const char *filename, int channels);

        ~image();

        void save(const char *filename) const;
};

#endif  /* IMAGE_HPP */