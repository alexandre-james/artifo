#include "color_reduction.hpp"


void median_cut(rgb_image *input, vector<vector<int>> bucket) {
    int r_sum = 0;
    int g_sum = 0;
    int b_sum = 0;
    int count = 0;

    // Parcourir le bucket et faire la moyenne des r g, b

    for (auto pixels: bucket) {
        r_sum += pixels[0];
        g_sum += pixels[1];
        b_sum += pixels[2];
        count += 1;
    }
    int r_average = r_sum / count;
    int g_average = g_sum / count;
    int b_average = b_sum / count;

    //Replacer dans l image d origine
    
    for (auto pixels: bucket) {
        input->pixels[pixels[4] * input->width * input->dim + pixels[3]] = r_average;
        input->pixels[pixels[4] * input->width * input->dim + pixels[3] + 1] = g_average;
        input->pixels[pixels[4] * input->width * input->dim + pixels[3] + 2] = b_average;
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

void split_into_buckets(rgb_image *img, vector<vector<int>> bucket, int channel, int depth) {
    
    if (bucket.size() == 0)
    {
        return;
    }
    if (depth == 0)
    {
        median_cut(img, bucket);
        return;
    }

    // Sort the pixels by that channel values.
    sort(bucket.begin(), bucket.end(), [channel](const vector<int> &a, const vector<int> &b) {
            return a[channel] < b[channel];
        });

    
    // Find the median and cut the region by that pixel.
    size_t median_index = ((bucket.size() + 1) / 2);
    cout << "Bucket size : " << bucket.size() << '\n'; 
    cout << "Median index : " << median_index << '\n'; 
    vector<vector<int>> first_part(bucket.begin(), bucket.begin() + median_index); //revoir si bien coupés
    vector<vector<int>> second_part(bucket.begin() + median_index, bucket.end());

    // Repeat the process for both buckets until you have the desired number of colors.
    split_into_buckets(img, first_part, channel, depth -1);
    split_into_buckets(img, second_part, channel, depth -1);
}



vector<vector<int>> create_bucket(rgb_image *input) {
    vector<vector<int>> bucket;
    
    for (int y = 0; y < input->height; y++) {
        for (int x = 0; x < input->width; x+=3) {
            vector<int> pixels;
            pixels.push_back(input->pixels[y * input->width * input->dim + x]);
            pixels.push_back(input->pixels[y * input->width * input->dim + x + 1]);
            pixels.push_back(input->pixels[y * input->width * input->dim + x + 2]);
            pixels.push_back(x);
            pixels.push_back(y);

            bucket.push_back(pixels);
        }
    }
    return bucket;
}




rgb_image *colorReduction(rgb_image *input, int nb_colors = 16) {

    rgb_image *output = new rgb_image(input->width, input->height);
    // Move all pixels into a single large bucket.
    vector<vector<int>> bucket = create_bucket(input);
    
    // Find the color channel in the image with the greatest range
    int channel = more_represented_channel(input);

    split_into_buckets(output, bucket, channel, 4);

    return output;
}