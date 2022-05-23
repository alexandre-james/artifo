#include "cartoon.hpp"

rgb_image *cartoon(rgb_image *input, int nb_colors, bool monochrom) {
    gray_image *gray = input->to_gray();
    gray_image *log = laplacian_of_gaussian(gray, 2, 0.95);

    int size = input->height / 200;
    mask *kernel = structuring_element(size, size);
    gray_image *convolution = convolve(log, kernel);
    gray_image *soften = multiply(convolution, 0.5);
    rgb_image *outlines = gray_to_rgb(soften);

    // Color reduction
    rgb_image *color_reduced = colorReduction(input, nb_colors, monochrom);

    // Fusion
    rgb_image *output = substract(color_reduced, outlines);

    delete gray;
    delete log;
    delete kernel;
    delete convolution;
    delete soften;
    delete outlines;
    delete color_reduced;

    return output;
}