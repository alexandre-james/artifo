#include "tv.hpp"
#include "../construct/salt_pepper.hpp"
#include "../image/conversion.hpp"
#include "../tools/contrast.hpp"
#include "../tools/manipulation.hpp"
#include "../modifier/transformation.hpp"
#include "../modifier/filter.hpp"

#include <cmath>
#include <cstdio>

rgb_image *tv(rgb_image *input) {
    int height = 10;
    int size = input->height / height / 4;
    point<int> center = point<int>(input->width / 2, input->height / 2);

    int nb_bugs = 5;
    int gap = input->height / nb_bugs / size * size;
    int min = size * 3;
    int max = min + size;

    rgb_image *waves = contrast(input, 0.95);

    for (int i = 0; i < nb_bugs; i++) {
        auto wave = [min, max, size](int x, int y) {
            if (y > min && y < max)
                return point<int>(x + size / 2 * sin(y * 2 * M_PI / size), y);
            return point<int>(x, y);
        };
        rgb_image *tmp = transform(waves, wave);
        delete waves;
        waves = tmp;

        min += gap;
        max += gap;
    }

    auto r_extend = [center](int x, int y) {
        double mult = 5. / center.x;
        return point<int>(x - (x - center.x) * mult, y - (y - center.y) * mult);
    };

    auto g_extend = [center](int x, int y) {
        double mult = 5. / center.x;
        return point<int>(x + (x - center.x) * mult, y + (y - center.y) * mult);
    };

    rgb_image *salt = salt_and_pepper(input->width, input->height, 1000, (float) sqrt((input->width + input->height) / 600));
    rgb_image *pepper = salt_and_pepper(input->width, input->height, 1000, (float) sqrt((input->width + input->height) / 600));
    rgb_image *salty = add(waves, salt);
    rgb_image *peppered = substract(salty, pepper);

    int kernel_size = sqrt((input->width + input->height) / 50);
    rgb_image *gauss = apply_channels(average, peppered, kernel_size, kernel_size);

    gray_image **channels = get_channels(gauss);
    gray_image **mod_channels = (gray_image **) malloc(input->dim * sizeof(gray_image *));

    mod_channels[0] = transform(channels[0], r_extend);
    mod_channels[1] = transform(channels[1], g_extend);
    mod_channels[2] = channels[2]->copy();

    rgb_image *merged = merge<rgb_image>(mod_channels);

    for (int y = 0; y < merged->height; y++) {
        int num = 10;
        if (sin(800. * y / (input->width + input->height)) > 0)
            num = -num;
        for (int x = 0; x < merged->width * merged->dim; x++) {
            merged->pixels[y * merged->width * merged->dim + x] = bound(merged->pixels[y * merged->width * merged->dim + x] + num);
        }
    }

    rgb_image *output = apply_channels(average, merged, kernel_size, kernel_size);

    delete waves;
    delete salt;
    delete pepper;
    delete salty;
    delete peppered;
    delete gauss;
    delete merged;
    
    for (int i = 0; i < input->dim; i++) {
        delete channels[i];
        delete mod_channels[i];
    }
    free(channels);
    free(mod_channels);
    
    return output;
}