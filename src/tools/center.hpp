#pragma once

#include "../image/gray_image.hpp"
#include "../construct/point.hpp"

int *get_colors(gray_image* image, int width, int height);

point<float> *get_centers(gray_image* image, int width, int height);

void paint(gray_image *image, int color, float radius, point<float> center);

void paint_hexagon(gray_image *input, int color, float radius, point<float> center);