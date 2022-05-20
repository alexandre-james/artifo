#include "color_reduction.hpp"

/*
uint8_t mean(template<im> *array) {
    int sum = 0;
    int length = sizeof(array);
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / length;
}*/

void quantize(rgb_image *input) {
    // Compute the mean value on each channel

    // store the new colors into the pixels
}

void median_cut(rgb_image *input, rgb_image *img_arr) {
    int* r_sum;
    int* g_sum;
    int* b_sum;

    for (int i = 0; i < img_arr->length; i++)
    {
        r_sum += img_arr->pixels[0];
        g_sum += img_arr->pixels[1];
        b_sum += img_arr->pixels[2];
    }
    
}

bool mostly(int max, int u, int v) {
    return max > u && max > v;
}

int more_represented_channel(rgb_image *image) {
    int r_count = 0;
    int g_count = 0;
    int b_count = 0;

    for (int i = 0; i < image->length; i+=3) {
        r_count += image->pixels[i + 0];
        g_count += image->pixels[i + 1];
        b_count += image->pixels[i + 2];
    }
    
    if (mostly(r_count, g_count, b_count)) {
        return 0;
    }   
    if (mostly(g_count, r_count, b_count)) {
        return 1;
    }   
    if (mostly(b_count, r_count, g_count)) {
        return 2;
    }
    else {
        return -1;
    }
        
}


int colorReduction(rgb_image *input) {

    // Find the color channel in the image with the greatest range
    //int channel = more_represented_channel(input);
    return 0;
    /*
    for (int i = 0; i < input->length; i++) {
        r_count += input->pixels[input->dim * i + channel];
    }
    */
    
}