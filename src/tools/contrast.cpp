#include "contrast.hpp"
#include "../image/conversion.hpp"

rgb_image *contrast(rgb_image* input, float threshold) {
    hsv_image *hsv = rgb_to_hsv(input);
    gray_image *v_channel = get_channel(hsv, V_CHANNEL);

    modifier<gray_image> *modif = new modifier(v_channel, threshold);
    gray_image *v_linear = modif->linear();

    hsv_image *result = set_channel(hsv, v_linear, V_CHANNEL);
    rgb_image *output = hsv_to_rgb(result);

    delete hsv;
    delete v_channel;
    delete modif;
    delete v_linear;
    delete result;

    return output;
}