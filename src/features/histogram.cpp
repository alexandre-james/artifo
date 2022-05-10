#include <algorithm>
#include <cmath>
#include <cstring>

#include "histogram.hpp"

histogram gray_histogram(const gray_image *image) {
    histogram histogram;

    for (int i=0; i < NB_LEVELS; ++i)
        histogram.columns[i] = 0;

    for (int offset=0; offset < image->length; ++offset)
        histogram.columns[image->pixels[offset]]++;

    return histogram;
}

rgba_image *histogram_to_image(const histogram histogram, const char *color) {
    int max = histogram.columns[0];
    for (int i = 0; i < NB_LEVELS; i++)
        max = std::max(max, (int) histogram.columns[i]);

    rgba_image *image = new rgba_image(NB_LEVELS, 5 * ((int) log(max) + 1));
    for (int i = 0; i < image->length; i++)
        image->pixels[i] = 0;

    for (int i = 0; i < image->width; i++) {
        double v = histogram.columns[i];
        double ratio = v / max;
        for (int j = 0; j < ratio * image->height; j++) {
            int y = (image->height - j - 1) * 4 * image->width;
            if (strcmp(color, "green") && strcmp(color, "blue"))
                image->pixels[4 * i + y] = i;
            if (strcmp(color, "red") && strcmp(color, "blue"))
                image->pixels[4 * i + 1 + y] = i;
            if (strcmp(color, "red") && strcmp(color, "green"))
                image->pixels[4 * i + 2 + y] = i;
            image->pixels[4 * i + 3 + y] = 255;
        }
    }

    return image;
}

void densest(histogram histogram, float threshold, int &min, int &max) {
  int length = 0;
  for (int i = 0; i < NB_LEVELS; i++)
    length += histogram.columns[i];

  int min_interval = NB_LEVELS;
  for (int i = 0; i < NB_LEVELS; i++) {
    int sum = 0;
    for (int j = i; j < NB_LEVELS && j < i + min_interval; j++) {
      sum += histogram.columns[j];
      if (sum > threshold * length) {
        min = i;
        max = j;
        min_interval = j - i;
      }
    }
  }
}