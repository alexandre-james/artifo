#include "saturation.hpp"
#include "../image/conversion.hpp"

rgb_image *saturate(rgb_image* input, float multiplier) {
  hsv_image *hsv = rgb_to_hsv(input);
  gray_image *saturation = get_channel(hsv, 1);

  for (int i = 0; i < saturation->length; i++) {
    int res = saturation->pixels[i] * multiplier;
    if (res > MAX_LEVEL)
      res = MAX_LEVEL;
    if (res < 0)
      res = 0;
    saturation->pixels[i] = res;
  }
  hsv_image *saturated_hsv = set_channel(hsv, saturation, 1);
  rgb_image *output = hsv_to_rgb(saturated_hsv);

  delete hsv;
  delete saturation;
  delete saturated_hsv;

  return output;
}