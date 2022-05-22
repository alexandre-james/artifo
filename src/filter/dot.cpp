#include "dot.hpp"
#include "../tools/center.hpp"
#include "../tools/manipulation.hpp"
#include "../image/gray_image.hpp"
#include "../image/rgb_image.hpp"
#include "../image/rgba_image.hpp"
#include "../image/hsv_image.hpp"

#include <cstdlib>

gray_image *gray_dot(gray_image *input, int height, float radius) {
	int width = height * (5. / 6);
	int *colors = get_colors(input, width, height);
	point *centers = get_centers(input, width, height);

	gray_image *output = new gray_image(input->width, input->height);

	for (int i = 0; i < input->length; i++) {
		output->pixels[i] = 0;
	}

	int *memory = (int*) calloc(output->length, sizeof(int));
	for (int i = 0; i < width * height; i++) {
		paint(output, memory, colors[i], radius, centers[i], centers[i]);
	}

	free(colors);
	free(centers);
	free(memory);
	return output;
}

template <typename image_type>
image_type *dot(image_type *input, int height, float radius) {
	return apply_channels(gray_dot, input, height, radius);
}

template gray_image *dot(gray_image *, int, float);
template rgb_image *dot(rgb_image *, int, float);
template rgba_image *dot(rgba_image *, int, float);
template hsv_image *dot(hsv_image *, int, float);