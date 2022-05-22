#include "center.hpp"

#include <cstdlib>
#include <cmath>

int *get_colors(gray_image* input, int width, int height) {
	// number of dots
	int length = width * height;

	long *sums = (long *) calloc(length, sizeof(long));
	int *sizes = (int *) calloc(length, sizeof(int));

    // sum colors
	for (int y = 0; y < input->height; y++) {
		for (int x = 0; x < input->width; x++) {
			int dx = width * x / input->width;
			int dy = height * y / input->height;
			sums[dy * width + dx] += input->pixels[y * input->width + x];
			sizes[dy * width + dx] += 1;
		}
	}

    // calc average color
	int *colors = (int *) malloc(length * sizeof(int));
	for (int i = 0; i < length; i++) {
		colors[i] = int(sums[i]) / sizes[i];
	}

	free(sums);
	free(sizes);
	return colors;
}

point<int> *get_centers(gray_image* input, int width, int height) {
	point<int> *centers = (point<int> *) malloc(width * height * sizeof(point<int>));
	for (int dy = 0; dy < height; dy++) {
		int y = dy * input->height / height + input->height / (2 * height);
		int start = 0;
		if (dy % 2 == 1) {
			start = input->width / (2 * width);
		}
		
		for (int dx = 0; dx < width; dx++) {
			int x = dx * input->width / width + start;
			centers[dy * width + dx] = point(x, y);
		}
	}

	return centers;
}

void paint(gray_image *input, int color, float radius, point<int> center) {
	for (int y = center.y - radius; y <= center.y + radius; y++) {
		for (int x = center.x - radius; x <= center.x + radius; x++) {
			if (x >= 0 && y >= 0 && x < input->width && y < input->height
				&& dist(center, point<int>(x, y)) < radius) {
				input->pixels[y * input->width + x] = color;
			}
		}
	}
}

bool in_hexagon(point<int> center, point<int> p, float radius) {
    float By = center.y - 2 * radius / (float) sqrt(3);
    float Dy = center.y + 2 * radius / (float) sqrt(3);
    float a = 1. / sqrt(3);
    auto f1 = [By, a, center] (int x) { return -a * x + By + a * center.x; };
    auto f2 = [By, a, center] (int x) { return a * x + By - a * center.x; };
    auto f3 = [Dy, a, center] (int x) { return -a * x + Dy + a * center.x; };
    auto f4 = [Dy, a, center] (int x) { return a * x + Dy - a * center.x; };
    return p.x > center.x - radius && p.x < center.x + radius
    && p.y > f1(p.x) && p.y > f2(p.x) && p.y < f3(p.x) && p.y < f4(p.x);
}

void paint_hexagon(gray_image *input, int color, float radius, point<int> center) {
	for (int y = center.y - radius * 2. / sqrt(3); y <= center.y + radius * 2. / sqrt(3); y++) {
		for (int x = center.x - radius; x <= center.x + radius; x++) {
			if (x >= 0 && y >= 0 && x < input->width && y < input->height
				&& in_hexagon(center, point<int>(x, y), radius)) {
				input->pixels[y * input->width + x] = color;
			}
		}
	}
}