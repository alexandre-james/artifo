#pragma once

#include "../image/conversion.hpp"
#include "../image/hsv_image.hpp"
#include "../image/rgb_image.hpp"
#include "../modifier/modifier.hpp"

rgb_image *contrast(rgb_image* input, float threshold);