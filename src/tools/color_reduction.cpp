#include "color_reduction.hpp"

int means(int *array) {
    int sum = 0;
    int length = sizeof(array);
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / length;
}

void quantize(rgb_image *input) {
    // Compute the mean value on each channel

    // store the new colors into the pixels
}

void median_cut(rgb_image *input) {

}

void colorReduction(rgb_image *input, int nb_colors = 64) {
    // Construction histo de couleurs

    // Elimination des extremites vides

    // Decoupage du parallelepipede restant en 2 sous blocs av autant de pnts

    // Pour chaque sous bloc, recommencer jusqu a nb couleurs

    // Pour chaque partie, trouver une couleur représentante
}