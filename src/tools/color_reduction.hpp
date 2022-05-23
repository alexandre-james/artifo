#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "../image/conversion.hpp"
#include "../image/hsv_image.hpp"
#include "../image/rgb_image.hpp"
#include "../modifier/modifier.hpp"
using namespace std;

rgb_image *colorReduction(rgb_image *input, int nb_colors = 16, bool monochrom = false);