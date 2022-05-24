#include "conversion.hpp"

#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>

gray_image *rgb_to_gray(const rgb_image *input) {
    return input->to_gray();
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

rgba_image *rgb_to_rgba(const rgb_image *input) {
    rgba_image *output = new rgba_image(input->width, input->height);

    for (int i = 0 ; i < input->width * input->height; i++) {
        output->pixels[4 * i] = input->pixels[3 * i];
        output->pixels[4 * i + 1] = input->pixels[3 * i + 1];
        output->pixels[4 * i + 2] = input->pixels[3 * i + 2];
        output->pixels[4 * i + 3] = 255;
    }
    return output; 
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
gray_image **get_channels(image_type *input) {
    gray_image **channels = (gray_image **) malloc(input->dim * sizeof(gray_image *));

    for (int i = 0; i < input->dim; i++) {
        channels[i] = new gray_image(input->width, input->height);
    }
    for (int i = 0; i < input->length; i++) {
        channels[i % input->dim]->pixels[i / input->dim] = input->pixels[i];
    }
    return channels;
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

template <typename image_type>
image_type *merge(gray_image **channels) {
    image_type *output = new image_type(channels[0]->width, channels[0]->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = channels[i % output->dim]->pixels[i / output->dim];
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
image_type *image_copy(image_type *input) {
    image_type *output = new image_type(input->width, input->height);
    memcpy(output->pixels, input->pixels, output->length);
    return output;
}

uint8_t bound(int nb) {
    if (nb > MAX_LEVEL)
        return MAX_LEVEL;
    if (nb < 0)
        return 0;
    return nb;
}

template <typename image_type>
image_type *add(image_type *input1, image_type *input2) {
    assert(input1->width == input2->width && input1->height == input2->height);

    image_type *output = new image_type(input1->width, input1->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = bound(input1->pixels[i] + input2->pixels[i]);
    }

    return output;
}

rgb_image *synthesis(rgb_image *input1, rgba_image *input2) {
    assert(input1->width == input2->width && input1->height == input2->height);

    rgb_image *output = new rgb_image(input1->width, input1->height);

    for (int i = 0; i < output->width * output->height; i++) {
        float opacity = ((255. - input2->pixels[4 * i + 3]) / 255);
        output->pixels[3 * i] = bound((input2->pixels[4 * i] + opacity * input1->pixels[3 * i]) / (1 + opacity));
        output->pixels[3 * i + 1] = bound((input2->pixels[4 * i + 1] + opacity * input1->pixels[3 * i + 1]) / (1 + opacity));
        output->pixels[3 * i + 2] = bound((input2->pixels[4 * i + 2] + opacity * input1->pixels[3 * i + 2]) / (1 + opacity));
    }

    return output;
}

template <typename image_type>
image_type *substract(image_type *input1, image_type *input2) {
    assert(input1->width == input2->width && input1->height == input2->height);

    image_type *output = new image_type(input1->width, input1->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = bound(input1->pixels[i] - input2->pixels[i]);
    }

    return output;  
}

template <typename image_type>
image_type *multiply(image_type *input, const float nb) {
    image_type *output = new image_type(input->width, input->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = bound(nb * input->pixels[i]);
    }

    return output;  
}

template <typename image_type>
image_type *inverse(image_type *input) {
    image_type *output = new image_type(input->width, input->height);

    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = MAX_LEVEL - input->pixels[i];
    }

    return output; 
}

template <typename image_type>
image_type *crop(image_type *input, int padding) {
    assert(input->width > 2 * padding && input->height > 2 * padding);

    image_type *output = new image_type(input->width - 2 * padding, input->height - 2 * padding);

    for (int y = padding; y < input->height - padding; y++) {
        for (int x = padding * input->dim; x < (input->width - padding) * input->dim; x++) {
            output->pixels[(y - padding) * output->width * output->dim + x - padding * output->dim] = input->pixels[y * input->width * input->dim + x];
        }
    }

    return output; 
}

template gray_image *get_channel(gray_image *, const int);
template gray_image *get_channel(rgb_image *, const int);
template gray_image *get_channel(rgba_image *, const int);
template gray_image *get_channel(hsv_image *, const int);

template gray_image **get_channels(gray_image *);
template gray_image **get_channels(rgb_image *);
template gray_image **get_channels(rgba_image *);
template gray_image **get_channels(hsv_image *);

template gray_image *set_channel(gray_image *, gray_image *, const int);
template rgb_image *set_channel(rgb_image *, gray_image *, const int);
template rgba_image *set_channel(rgba_image *, gray_image *, const int);
template hsv_image *set_channel(hsv_image *, gray_image *, const int);

template gray_image *merge(gray_image **);
template rgb_image *merge(gray_image **);
template rgba_image *merge(gray_image **);
template hsv_image *merge(gray_image **);

template gray_image *image_copy(gray_image *);
template rgb_image *image_copy(rgb_image *);
template rgba_image *image_copy(rgba_image *);
template hsv_image *image_copy(hsv_image *);

template gray_image *add(gray_image *, gray_image *);
template rgb_image *add(rgb_image *, rgb_image *);
template rgba_image *add(rgba_image *, rgba_image *);
template hsv_image *add(hsv_image *, hsv_image *);

template gray_image *substract(gray_image *, gray_image *);
template rgb_image *substract(rgb_image *, rgb_image *);
template rgba_image *substract(rgba_image *, rgba_image *);
template hsv_image *substract(hsv_image *, hsv_image *);

template gray_image *multiply(gray_image *, const float);
template rgb_image *multiply(rgb_image *, const float);
template rgba_image *multiply(rgba_image *, const float);
template hsv_image *multiply(hsv_image *, const float);

template gray_image *inverse(gray_image *);
template rgb_image *inverse(rgb_image *);
template rgba_image *inverse(rgba_image *);
template hsv_image *inverse(hsv_image *);

template gray_image *crop(gray_image *, int);
template rgb_image *crop(rgb_image *, int);
template rgba_image *crop(rgba_image *, int);
template hsv_image *crop(hsv_image *, int);