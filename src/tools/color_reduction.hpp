#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include "../image/conversion.hpp"
#include "../image/hsv_image.hpp"
#include "../image/rgb_image.hpp"
#include "../modifier/modifier.hpp"
using namespace std;

int colorReduction(rgb_image *input, int nb_colors);