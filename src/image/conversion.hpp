#pragma once

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
gray_image **get_channels(image_type *input);

template <typename image_type>
image_type *set_channel(image_type *input, gray_image *channel, const int nb);

template <typename image_type>
image_type *merge(gray_image **channels);

rgb_image* merge(gray_image *red, gray_image *green, gray_image *blue);

template <typename image_type>
image_type *image_copy(image_type *input);

uint8_t bound(int nb);

template <typename image_type>
image_type *add(image_type *input1, image_type *input2);

template <typename image_type>
image_type *substract(image_type *input1, image_type *input2);

template <typename image_type>
image_type *multiply(image_type *input, const float nb);

template <typename image_type>
image_type *inverse(image_type *input);

template <typename image_type>
image_type *crop(image_type *input, int padding);