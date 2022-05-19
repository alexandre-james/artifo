#pragma once

#include "../image/gray_image.hpp"

template <typename image_type>
image_type *apply_channels(gray_image *(*function)(gray_image *), image_type *input);

template <typename image_type>
image_type *apply_channels(gray_image *(*function)(gray_image *, int, int), image_type *input, int width, int height);