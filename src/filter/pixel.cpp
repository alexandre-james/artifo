#include "pixel.hpp"
#include "../tools/resolution.hpp"
#include "../tools/manipulation.hpp"
#include "../tools/saturation.hpp"
#include "../tools/contrast.hpp"
#include "../tools/edge.hpp"
#include "../image/conversion.hpp"
#include "../modifier/modifier.hpp"
#include "../modifier/convolution.hpp"
#include "../modifier/filter.hpp"
#include "../modifier/structure.hpp"

rgb_image *pixel(rgb_image *input, int height, int divisions, bool outline) {
    rgb_image *pretreated;

    if (outline) {
        gray_image *gray = input->to_gray();
        gray_image *log = laplacian_of_gaussian(gray, 2, 0.95);

        int size = height / 5;
        mask *kernel = structuring_element(size, size);
        gray_image *convolution = convolve(log, kernel);
        gray_image *soften = multiply(convolution, 0.5);
        rgb_image *outlines = gray_to_rgb(soften);

        pretreated = substract(input, outlines);

        delete gray;
        delete log;
        delete kernel;
        delete convolution;
        delete soften;
        delete outlines;
    }
    else {
        pretreated = image_copy(input);
    }

    rgb_image *pixelized = apply_channels(pixelize, pretreated, height, 0);

    double y_ratio = (double) height / input->height;
    int width = input->width * y_ratio;

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

    rgb_image *output = add(pixelized, grid);

    delete pretreated;
    delete pixelized;
    delete grid;

    return output;
}