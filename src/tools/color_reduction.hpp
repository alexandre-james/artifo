#pragma once

#include <vector>
#include <iostream>
#include "../image/conversion.hpp"
#include "../image/hsv_image.hpp"
#include "../image/rgb_image.hpp"
#include "../modifier/modifier.hpp"

int colorReduction(rgb_image *input);
int more_represented_channel(rgb_image *image);