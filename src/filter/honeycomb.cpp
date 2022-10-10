#include "honeycomb.hpp"
#include "../tools/center.hpp"
#include "../tools/manipulation.hpp"
#include "../image/conversion.hpp"

#include <cstdlib>
#include <cmath>

#include <cstdio>

gray_image *gray_honeycomb(gray_image *input, int width, float radius) {
	int height = (double) width * (2. / sqrt(3)) * input->height / input->width;
	int *colors = get_colors(input, width, height);
	point<float> *centers = get_centers(input, width, height);

	gray_image *output = new gray_image(input->width, input->height);

    for (int i = 0; i < width * height; i++) {
		paint_hexagon(output, bound(colors[i] - 10), radius * 1.3, centers[i]);
	}

	for (int i = 0; i < width * height; i++) {
		paint_hexagon(output, colors[i], radius, centers[i]);
	}

	free(colors);
	free(centers);
	return output;
}

template <typename image_type>
image_type *honeycomb(image_type *input, int width, bool is_crop) {
    float radius = (float) input->width * sqrt(3) / (4 * width);
    image_type *output = apply_channels(gray_honeycomb, input, width, radius);

    if (is_crop) {
        image_type *tmp = crop(output, radius);
        delete output;
        output = tmp;
    }
    return output;
}

template gray_image *honeycomb(gray_image *, int, bool);
template rgb_image *honeycomb(rgb_image *, int, bool);
template rgba_image *honeycomb(rgba_image *, int, bool);
template hsv_image *honeycomb(hsv_image *, int, bool);