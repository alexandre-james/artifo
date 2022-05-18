#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include "gray_image.hpp"
#include "rgb_image.hpp"
#include "rgba_image.hpp"
#include "hsv_image.hpp"

#include <typeinfo>
#include <cassert>

/** From rgb **/
gray_image *rgb_to_gray(const rgb_image *input);
hsv_image *rgb_to_hsv(const rgb_image *input);

/** To rgb **/
rgb_image *gray_to_rgb(const gray_image *input);
rgb_image *hsv_to_rgb(const hsv_image *input);

template <typename image_type>
gray_image *get_channel(image_type *input, const int nb);

template <typename image_type>
image_type *set_channel(image_type *input, gray_image *channel, const int nb);

rgb_image* merge(gray_image *red, gray_image *green, gray_image *blue);

template <typename image_type>
image_type *image_copy(image_type* input);

#endif  /* CONVERSION_HPP */