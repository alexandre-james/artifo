#pragma once

#include "../image/gray_image.hpp"

template <typename image_type>
image_type *apply_channels(gray_image *(*function)(gray_image *), image_type *input);

template <typename image_type, typename num_type1, typename num_type2>
image_type *apply_channels(gray_image *(*function)(gray_image *, num_type1, num_type2),
image_type *input, num_type1 num1, num_type2 num2);