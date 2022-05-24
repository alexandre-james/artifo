#pragma once

#include "../image/gray_image.hpp"
#include "../construct/point.hpp"

int *get_colors(gray_image* image, int width, int height);

point<float> *get_centers(gray_image* image, int width, int height);

template <typename image_type>
void paint(image_type *input, int color, float radius, point<float> center);

template <typename image_type>
void paint_hexagon(image_type *input, int color, float radius, point<float> center);