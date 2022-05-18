#pragma once

#include "../image/gray_image.hpp"

template <typename image_type>
image_type *apply_channels(image_type *input, gray_image *(*function)(gray_image *));