#include "conversion.hpp"

#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>

gray_image *rgb_to_gray(const rgb_image *input) {
    gray_image *output = new gray_image(input->width, input->height);
    for (int i = 0 ; i < output->length ; i++) {
        output->pixels[i] = 0.299 * input->pixels[3 * i]
        + 0.587 * input->pixels[3 * i + 1]
        + 0.114 * input->pixels[3 * i + 2];
    }
    return output;
}

hsv_image *rgb_to_hsv(const rgb_image *input) {
    hsv_image *hsv = new hsv_image(input->width, input->height);

    for (int i = 0; i+3 < input->length; i+=3)
    {
        double rp = (double) input->pixels[i] / 255;
        double gp = (double) input->pixels[i+1] / 255;
        double bp = (double) input->pixels[i+2] / 255;

        double cmax = std::max(rp, gp);
        double cmin = std::min(rp, gp);
        cmax = std::max(cmax, bp);
        cmin = std::min(cmin, bp);
        double delta = cmax - cmin;

        int h;
        if (delta == 0)
        h = 0;
        else if (cmax == rp)
        h = 60 * std::fmod(((gp - bp) / delta), 6);
        else if (cmax == gp)
        h = 60 * ((bp - rp) / delta + 2);
        else
        h = 60 * ((rp - gp) / delta + 4);

        hsv->pixels[i] = h * 255 / 360;
        hsv->pixels[i+1] = (cmax == 0) ? 0 : delta / cmax * 255;
        hsv->pixels[i+2] = cmax * 255;
    }
    return hsv;
}

rgb_image *gray_to_rgb(const gray_image *input) {
    rgb_image *output = new rgb_image(input->width, input->height);

    for (int i = 0 ; i < input->length ; i++) {
        output->pixels[3 * i] = input->pixels[i];
        output->pixels[3 * i + 1] = input->pixels[i];
        output->pixels[3 * i + 2] = input->pixels[i];
    }
    return output;
}

rgb_image *hsv_to_rgb(const hsv_image *input) {
    rgb_image *rgb = new rgb_image(input->width, input->height);

    for (int i = 0; i < input->length; i+=3)
    {
        double h = input->pixels[i] * 360 / 255;
        double s = (double) input->pixels[i+1] / 255;
        double v = (double) input->pixels[i+2] / 255;

        double c = v * s;
        double x = c * (1 - std::abs(std::fmod(h / 60, 2) - 1));
        double m = v - c;
        double rp, gp, bp;
        if (h < 60)
        rp = c, gp = x, bp = 0;
        else if (h < 120)
        rp = x, gp = c, bp = 0;
        else if (h < 180)
        rp = 0, gp = c, bp = x;
        else if (h < 240)
        rp = 0, gp = x, bp = c;
        else if (h < 300)
        rp = x, gp = 0, bp = c;
        else
        rp = c, gp = 0, bp = x;

        rgb->pixels[i] = (rp + m) * 255;
        rgb->pixels[i+1] = (gp + m) * 255;
        rgb->pixels[i+2] = (bp + m) * 255;
    }
    return rgb;
}

template <typename image_type>
gray_image *get_channel(image_type *input, const int nb) {
    assert(nb < input->dim);

    gray_image *output = new gray_image(input->width, input->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = input->pixels[input->dim * i + nb];
    }
    return output;
}

template <typename image_type>
image_type *set_channel(image_type *input, gray_image *channel, const int nb) {
    assert(nb < input->dim && channel->length * input->dim == input->length);

    image_type *output = new image_type(input->width, input->height);

    for (int i = 0; i < output->length; i++) {
        if (i % output->dim == nb) {
            output->pixels[i] = channel->pixels[i / output->dim];
        }
        else {
            output->pixels[i] = input->pixels[i];
        }
    }
    return output;
}

rgb_image* merge(gray_image *red, gray_image *green, gray_image *blue) {
    assert(red->length == green->length && red->length == blue->length);
    rgb_image *output = new rgb_image(red->width, red->height);

    for(int i = 0; i < red->length; i++) {
    output->pixels[3*i] = red->pixels[i];
    output->pixels[3*i+1] = green->pixels[i];
    output->pixels[3*i+2] = blue->pixels[i];
    }

    return output;
}

template <typename image_type>
image_type *image_copy(image_type* input) {
    image_type *output = new image_type(input->width, input->height);
    memcpy(output->pixels, input->pixels, output->length);
    return output;
}

template gray_image* get_channel<gray_image>(gray_image *input, const int nb);
template gray_image* get_channel<rgb_image>(rgb_image *input, const int nb);
template gray_image* get_channel<rgba_image>(rgba_image *input, const int nb);
template gray_image* get_channel<hsv_image>(hsv_image *input, const int nb);

template gray_image *set_channel<gray_image>(gray_image *input, gray_image *channel, const int nb);
template rgb_image *set_channel<rgb_image>(rgb_image *input, gray_image *channel, const int nb);
template rgba_image *set_channel<rgba_image>(rgba_image *input, gray_image *channel, const int nb);
template hsv_image *set_channel<hsv_image>(hsv_image *input, gray_image *channel, const int nb);

template gray_image *image_copy<gray_image>(gray_image* input);
template rgb_image *image_copy<rgb_image>(rgb_image* input);
template rgba_image *image_copy<rgba_image>(rgba_image* input);
template hsv_image *image_copy<hsv_image>(hsv_image* input);