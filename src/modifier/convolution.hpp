#pragma once

#include "mask.hpp"

template <typename image_type>
image_type *convolve(image_type *input, mask *kernel);