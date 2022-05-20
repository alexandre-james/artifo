#include "convolution.hpp"
#include "../image/conversion.hpp"

template <typename image_type>
image_type *convolve(image_type *input, mask *kernel) {
    image_type *output = new image_type(input->width, input->height);
    for (int y = 0; y < output->height; y++) {
        for (int x = 0; x < output->width * input->dim; x++) {
            float sum = 0;
            for (int i = 0; i < kernel->height; i++) {
                for (int j = 0; j < kernel->width; j++) {
                    int y_pos = y - kernel->height / 2 + i;
                    int x_pos = x - kernel->width / 2 + j;
                    uint8_t value = 0;
                    if (x_pos >= 0 && y_pos >= 0 && y_pos < input->height && x_pos < input->width * output->dim)
                        value = input->pixels[y_pos * input->width * input->dim + x_pos];
                    sum += (float) kernel->values[i * kernel->width + j] * value;
                }
            }
            output->pixels[y * output->width * output->dim + x] = bound(sum);
        }
    }
    return output;
}

template gray_image *convolve(gray_image *, mask *);
template rgb_image *convolve(rgb_image *, mask *);
template rgba_image *convolve(rgba_image *, mask *);
template hsv_image *convolve(hsv_image *, mask *);