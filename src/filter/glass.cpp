#include "glass.hpp"
#include "../image/conversion.hpp"
#include "../modifier/transformation.hpp"

#include <cmath>

rgb_image *glass(rgb_image *input, int width, bool grid) {
    double size = (double) input->width / (width * 2 * M_PI);

    auto f = [size](int x, int y) {
        return point<int>(x + size * sin((double) x / size), y + size * sin((double) y / size));
    };

    rgb_image *transformed = transform(input, f);

    if (grid) {
        int divisions = 1;

        double y_ratio = (double) width / input->width;
        double height = input->height * y_ratio;

        rgb_image *grid = new rgb_image(input->width, input->height);

        for (int i = 0; i < grid->length; i ++) {
            grid->pixels[i] = 0;
        }

        for (int y = 0; y < height * divisions; y++) {
            for (int x = 0; x < input->width * input->dim; x++) {
                int y_pos = y * (double) input->height / height / divisions;
                grid->pixels[y_pos * input->width * input->dim + x] = 50;
            }
        }

        for (int y = 0; y < input->height; y++) {
            for (int x = 0; x < width * divisions; x++) {
                int x_pos = x * (double) input->width / width / divisions;
                grid->pixels[y * input->width * input->dim + x_pos * input->dim] = 50;
                grid->pixels[y * input->width * input->dim + x_pos * input->dim + 1] = 50;
                grid->pixels[y * input->width * input->dim + x_pos * input->dim + 2] = 50;
            }
        }
        rgb_image *output = add(transformed, grid);
        delete transformed;
        delete grid;

        return output;
    }
    else {
        return transformed;
    }
}