#pragma once

#include "../image/rgb_image.hpp"
#include "../tools/resolution.hpp"
#include "../tools/manipulation.hpp"
#include "../tools/saturation.hpp"
#include "../tools/contrast.hpp"
#include "../tools/edge.hpp"
#include "../tools/color_reduction.hpp"
#include "../image/conversion.hpp"
#include "../modifier/modifier.hpp"
#include "../modifier/convolution.hpp"
#include "../modifier/filter.hpp"
#include "../modifier/structure.hpp"

rgb_image *cartoon(rgb_image *input, int height);