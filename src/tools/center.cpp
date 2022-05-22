#include "center.hpp"

#include <cstdlib>

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

point *get_centers(gray_image* input, int width, int height) {
	point *centers = (point *) malloc(width * height * sizeof(point));
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

void paint(gray_image *input, int memory[], int color, float radius, point center, point p) {
	if (p.x >= 0 && p.y >= 0 && p.x < input->width && p.y < input->height
		&& center.dist(p) < radius && memory[p.y * input->width + p.x] == 0) {
		input->pixels[p.y*input->width + p.x] = color;
		memory[p.y * input->width + p.x] = 1;
		paint(input, memory, color, radius, center, point(p.x+1, p.y));
		paint(input, memory, color, radius, center, point(p.x, p.y+1));
		paint(input, memory, color, radius, center, point(p.x-1, p.y));
		paint(input, memory, color, radius, center, point(p.x, p.y-1));
	}
}