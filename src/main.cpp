#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

int main() {
    const char *filename = "input/image.png";
    int x,y,n;
    if (stbi_info(filename, &x, &y, &n)) {
        int width, height, bpp;

        uint8_t* rgb_image = stbi_load(filename, &width, &height, &bpp, 3);

        printf("width: %d\n", width);

        stbi_image_free(rgb_image);

        return 0;
    }
    else {
        printf("error: can't open image\n");
        return 1;
    }
}