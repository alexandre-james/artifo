#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

class image {
    public:
        int width, height, channels, length;

        uint8_t *pixels = nullptr;

        image(int width, int height, int channels);

        image(const char *filename, int channels);

        ~image();

        void save(const char *filename) const;
};

#endif  /* IMAGE_H */