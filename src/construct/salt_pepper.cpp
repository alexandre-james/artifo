#include "salt_pepper.hpp"
#include "point.hpp"
#include "../tools/center.hpp"

#include <cstdlib>

rgb_image *salt_and_pepper(int width, int height, int nb_dots, float radius) {
    rgb_image *output = new rgb_image(width, height);
    for (int i = 0; i < output->length; i++) {
        output->pixels[i] = 0;
    }

    for (int i = 0; i < nb_dots; i++) {
        paint(output, 50, radius, point<float>(rand() % width, rand() % height));
    }

    return output;
}