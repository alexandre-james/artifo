#include "color_reduction.hpp"

void median_cut(rgb_image *input, vector<vector<int>> bucket) {
    float r_sum = 0;
    float g_sum = 0;
    float b_sum = 0;
    float count = 0;

    // Parcourir le bucket et faire la moyenne des r g, b

    for (auto pixels: bucket) {
        r_sum += pixels[0];
        g_sum += pixels[1];
        b_sum += pixels[2];
        count += 1;
    }
    float r_average = r_sum / count;
    float g_average = g_sum / count;
    float b_average = b_sum / count;
    //TODO: voir pour la moyenne des couleurs

    //Replacer dans l image d origine
    for (auto pixels: bucket) {
        input->pixels[pixels[4] * input->width * input->dim + pixels[3]] = r_average;
        input->pixels[pixels[4] * input->width * input->dim + pixels[3] + 1] = g_average;
        input->pixels[pixels[4] * input->width * input->dim + pixels[3] + 2] = b_average;
    }
}

int more_represented_channel(vector<vector<int>> bucket) {
    int r_count = 0;
    int g_count = 0;
    int b_count = 0;

    for (size_t i = 0; i < bucket.size(); i++) {
        r_count += bucket[i][0];
        g_count += bucket[i][1];
        b_count += bucket[i][2];
    }

    if (r_count >= b_count && r_count >= g_count)
        return 0;
    else if (g_count >= r_count && g_count >= b_count)
        return 1;
    return 2;     
}

int get_min(vector<vector<int>> bucket, int channel) {
    int min = MAX_LEVEL;
    for (size_t i = 0; i < bucket.size(); i++) {
        min = std::min(min, bucket[i][channel]);
    }
    return min;
}

int get_max(vector<vector<int>> bucket, int channel) {
    int max = 0;
    for (size_t i = 0; i < bucket.size(); i++) {
        max = std::max(max, bucket[i][channel]);
    }
    return max;
}

int get_highest_range(vector<vector<int>> bucket) {
    // Find the color channel in the image with the greatest range
    int r_range = get_max(bucket, RED_CHANNEL) - get_min(bucket, RED_CHANNEL);
    int g_range = get_max(bucket, GREEN_CHANNEL) - get_min(bucket, GREEN_CHANNEL);
    int b_range = get_max(bucket, BLUE_CHANNEL) - get_min(bucket, BLUE_CHANNEL);

    if (r_range >= b_range && r_range >= g_range)
        return 0;
    else if (g_range >= r_range && g_range >= b_range)
        return 1;
    return 2;  
}

void split_into_buckets(rgb_image *img, vector<vector<int>> bucket, int depth, bool monochrom) {
    
    if (bucket.size() == 0)
    {
        return;
    }
    if (depth == 0)
    {
        median_cut(img, bucket);
        return;
    }

    int channel;
    if (monochrom)
        channel = more_represented_channel(bucket);
    else
        channel = get_highest_range(bucket);

    // Sort the pixels by that channel values.
    sort(bucket.begin(), bucket.end(), [channel](const vector<int> &a, const vector<int> &b) {
            return a[channel] < b[channel];
        });

    
    // Find the median and cut the region by that pixel.
    size_t median_index = ((bucket.size() + 1) / 2);
    
    vector<vector<int>> first_part(bucket.begin(), bucket.begin() + median_index); //revoir si bien coupés
    vector<vector<int>> second_part(bucket.begin() + median_index, bucket.end());

    // Repeat the process for both buckets until you have the desired number of colors.
    split_into_buckets(img, first_part, depth -1, monochrom);
    split_into_buckets(img, second_part, depth -1, monochrom);
}

vector<vector<int>> create_bucket(rgb_image *input) {
    vector<vector<int>> bucket;
    
    for (int y = 0; y < input->height; y++) {
        for (int x = 0; x < input->width * input->dim; x+=3) {
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

rgb_image *colorReduction(rgb_image *input, int nb_colors, bool monochrom) {

    rgb_image *output = new rgb_image(input->width, input->height);
    // Move all pixels into a single large bucket.
    vector<vector<int>> bucket = create_bucket(input);

    split_into_buckets(output, bucket, nb_colors, monochrom);

    return output;
}