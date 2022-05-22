#pragma once

#include "../image/gray_image.hpp"
#include "../construct/point.hpp"

int *get_colors(gray_image* image, int width, int height);

point *get_centers(gray_image* image, int width, int height);

void paint(gray_image *image, int memory[], int color, float radius, point center, point p);