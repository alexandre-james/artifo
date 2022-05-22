#include "dot.hpp"
#include "../tools/center.hpp"
#include "../tools/manipulation.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>
#include <cmath>

#include <cstdio>

gray_image *gray_alveolus(gray_image *input, int width, float radius) {
	int height = (double) width * (2. / sqrt(3)) * input->height / input->width;
	int *colors = get_colors(input, width, height);
	point<float> *centers = get_centers(input, width, height);

	gray_image *output = new gray_image(input->width, input->height);

	for (int i = 0; i < input->length; i++) {
		output->pixels[i] = 0;
	}

	for (int i = 0; i < width * height; i++) {
		paint_hexagon(output, colors[i], radius, centers[i]);
	}

	free(colors);
	free(centers);
	return output;
}

template <typename image_type>
image_type *alveolus(image_type *input, int width) {
	gray_image **channels = get_channels(input);
    float radius = (float) input->width * sqrt(3) / (4 * width);

    for (int i = 0; i < input->dim; i++) {
        gray_image *channel = gray_alveolus(channels[i], width, radius);
		width = width * (2. / 3);
        if (width == 0)
            width = 1;
        radius = (float) input->width * sqrt(3) / (4 * width);
        delete channels[i];
        channels[i] = channel;
    }
    image_type *merged = merge<image_type>(channels);
    image_type *output = crop(merged, radius);

    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
    }
    free(channels);
    delete merged;

    return output;
}

template gray_image *alveolus(gray_image *, int);
template rgb_image *alveolus(rgb_image *, int);
template rgba_image *alveolus(rgba_image *, int);
template hsv_image *alveolus(hsv_image *, int);