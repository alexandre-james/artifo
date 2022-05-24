#include "dot.hpp"
#include "../construct/mask.hpp"
#include "../construct/structure.hpp"
#include "../tools/center.hpp"
#include "../tools/manipulation.hpp"
#include "../image/conversion.hpp"
#include "../modifier/convolution.hpp"

#include <cstdlib>
#include <cmath>

gray_image *gray_dot(gray_image *input, int width, float radius) {
	int height = (double) width * (2. / sqrt(3)) * input->height / input->width;
	int *colors = get_colors(input, width, height);
	point<float> *centers = get_centers(input, width, height);

	gray_image *output = new gray_image(input->width, input->height);

	for (int i = 0; i < input->length; i++) {
		output->pixels[i] = 0;
	}

	for (int i = 0; i < width * height; i++) {
		paint(output, colors[i], radius, centers[i]);
	}

	free(colors);
	free(centers);
	return output;
}

template <typename image_type>
image_type *dot(image_type *input, int width, bool is_crop) {
	gray_image **channels = get_channels(input);
    float radius = (float) input->width * sqrt(3) / (4 * width);

    for (int i = 0; i < input->dim; i++) {
        gray_image *channel = gray_dot(channels[i], width, radius);

		width = width * (2. / 3);
        if (width == 0)
            width = 1;
        radius = (float) input->width * sqrt(3) / (4 * width);

        delete channels[i];
        channels[i] = channel;
    }
    image_type *output = merge<image_type>(channels);

    if (is_crop) {
        image_type *tmp = crop(output, radius);
        delete output;
        output = tmp;
    }

    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
    }
    free(channels);

    return output;
}

template gray_image *dot(gray_image *, int, bool);
template rgb_image *dot(rgb_image *, int, bool);
template rgba_image *dot(rgba_image *, int, bool);
template hsv_image *dot(hsv_image *, int, bool);