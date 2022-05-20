#include "color_reduction.hpp"


void median_cut(rgb_image *input, vector<vector<int>> bucket) {
    int r_sum = 0;
    int g_sum = 0;
    int b_sum = 0;

    // Parcourir le bucket 
    // Faire la moyenne des r g, b

    for (int i = 0; i < input->length; i+=3)
    {
        r_sum += input->pixels[i];
        g_sum += input->pixels[i + 1];
        b_sum += input->pixels[i + 2];
    }
    int r_average = r_sum / (input->length / 3);
    int g_average = g_sum / (input->length / 3);
    int b_average = b_sum / (input->length / 3);

    //Replacer dans l image d origine
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

void split_into_buckets(rgb_image *img, vector<vector<int>> bucket, int depth, int channel) {
    
    if (bucket.size() == 0)
    {
        return;
    }
    if (depth == 0)
    {
        // TODO: median_cut(img, bucket);
        return;
    }

    // Sort the pixels by that channel values.
    sort(bucket.begin(), bucket.end(), [channel](const vector<int> &a, const vector<int> &b) {
            return a[channel] < b[channel];
        });

    
    // Find the median and cut the region by that pixel.
    size_t median_index = ((bucket.size() + 1) / 2);
    vector<vector<int>> first_part(bucket.begin(), bucket.begin() + median_index); //revoir si bien coupés
    vector<vector<int>> second_part(bucket.begin() + median_index, bucket.end());

    // Repeat the process for both buckets until you have the desired number of colors.
    split_into_buckets(img, first_part, depth -1, channel);
    split_into_buckets(img, second_part, depth -1, channel);
}


int colorReduction(rgb_image *input, int nb_colors) {

    // Move all pixels into a single large bucket.
    vector<vector<int>> bucket;
    for (int i = 0; i < input->length; i+=3) {
        vector<int> pixels;
        pixels.push_back(input->pixels[i]);
        pixels.push_back(input->pixels[i + 1]);
        pixels.push_back(input->pixels[i + 2]);

        bucket.push_back(pixels);
    }

    // Find the color channel in the image with the greatest range
    int channel = more_represented_channel(input);

    split_into_buckets(input, bucket, 4, channel);

    return 0;
}