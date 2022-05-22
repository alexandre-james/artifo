#pragma once

#include "../image/gray_image.hpp"
#include "../construct/point.hpp"

int *get_colors(gray_image* image, int width, int height);

point<int> *get_centers(gray_image* image, int width, int height);

void paint(gray_image *image, int color, float radius, point<int> center);

void paint_hexagon(gray_image *input, int color, float radius, point<int> center);