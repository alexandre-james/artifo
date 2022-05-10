#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include "gray_image.hpp"
#include "rgb_image.hpp"
#include "rgba_image.hpp"

gray_image *rgb_to_gray(const rgb_image *input);

rgb_image *gray_to_rgb(const gray_image *input);

#endif  /* CONVERSION_HPP */