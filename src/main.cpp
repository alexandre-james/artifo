#include "image/conversion.hpp"
#include "features/histogram.hpp"
#include "modifier/modifier.hpp"
#include "modifier/filter.hpp"
#include "tools/saturation.hpp"
#include "tools/contrast.hpp"
#include "tools/manipulation.hpp"
#include "tools/sharpness.hpp"
#include "tools/edge.hpp"
#include "tools/resolution.hpp"
#include "filter/pixel.hpp"

#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <dirent.h>
#include <cstdlib>
#include <string>
#include <iostream>

int is_image(char *filename)
{
  filename = strrchr(filename, '.');

  if (filename != NULL)
    return !(strcmp(filename, ".jpg") && strcmp(filename, ".png"));

  return false;
}

char *get_name(char *output, const char *filename) {
    int i = 0;
    while (filename[i] != 0) {
        i++;
    }
    while (i >= 0 && filename[i] != '/') {
        i--;
    }
    strcpy(output, filename + i + 1);
    return output;
}

rgb_image *filter(rgb_image *input, int argc, char **argv) {
    if (!strcmp(argv[1], "pixel")) {
        if (argc < 6) {
            fprintf(stderr, "Invalid parameters\nformat: ./tifo pixel <file_path/all> <height: int> <divisions: int> <outline: bool>\n");
            exit(1);
        }
        return pixel(input, atoi(argv[3]), atoi(argv[4]), strcmp(argv[5], "false") && strcmp(argv[5], "0"));
    }
    fprintf(stderr, "Invalid parameters: this filter doesn't exist\nformat: ./tifo <filter> <file_path/all> <args...>\n");
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Invalid parameters\nformat: ./tifo <filter> <file_path/all> <args...>\n");
        return 1;
    }

    char **filenames;
    int nb_files = 0;
    bool all = !strcmp(argv[2], "all");

    if (all) {
        DIR *dr = opendir("input");
        if (dr == NULL)
        {
            mkdir("input", 0777);
            printf("Please insert images in input/ directory\n");
            return 0;
        }
        struct dirent *de;
        while ((de = readdir(dr)) != NULL) {
            if (is_image(de->d_name))
                nb_files++;
        }

        if (nb_files == 0) {
            printf("Please insert images in input/ directory\n");
            return 0;
        }

        filenames = (char **) malloc(nb_files * sizeof(char *));

        int i = 0;
        seekdir(dr, 0);
        while ((de = readdir(dr)) != NULL) {
            if (is_image(de->d_name))
                filenames[i++] = de->d_name;
        }
        
        closedir(dr);
    }
    else {
        nb_files = 1;
        filenames = (char **) malloc(sizeof(char *));
        filenames[0] = argv[2];
    }

    printf("nb_files: %d\n", nb_files);

    if (access("output", F_OK))
        mkdir("output", 0777);

    for (int i = 0; i < nb_files; i++) {
        printf("filenames[i]: %s\n", filenames[i]);
        char filename[100];
        char name[100];
        if (all) {
            strcpy(filename, "input/");
            strcat(filename, filenames[i]);
        }
        else {
            strcpy(filename, filenames[i]);
        }
        printf("filename: %s\n", filename);

        rgb_image *input = new rgb_image(filename);
        rgb_image *output = filter(input, argc, argv);

        strcpy(filename, "output/");
        strcat(filename, get_name(name, filenames[i]));
        output->save(filename);

        delete input;
        delete output;
    }

    free(filenames);

    /*

    gray_image *blue = get_channel(image, BLUE_CHANNEL);

    modifier<gray_image> *modifer = new modifier(blue);

    rgba_image *hist = histogram_to_image(modifer->histograms[0]);

    gray_image *blue_linear = modifer->linear();

    rgb_image *result = set_channel(image, blue_linear, BLUE_CHANNEL);

    hist->save("hist.png");
    result->save("test-linear.png");
    blue->save("test-blue.png");
    blue_linear->save("test-blue_linear.png");

    delete hist;
    delete image;
    delete blue;
    delete modifer;
    delete blue_linear;
    delete result;

    int size = 3;
    float sigma = 0.84089642;

    if (access("output", F_OK))
        mkdir("output", 0777);
 
    rgb_image *result = gaussian(image, size, sigma);
    result->save("output/pure-gaussian.png");

    rgb_image *result2 = apply_channels(gaussian, image, size, sigma);
    result2->save("output/chan-gaussian.png");

    gray_image *gray = image->to_gray();
    gray_image *result3 = gaussian(gray, size, sigma);
    result3->save("output/gray-gaussian.png");

    gray_image *diff = multiply(difference_of_gaussian(gray, 2), 5);
    diff->save("output/diff.png");

    delete diff;

    delete result3;
    delete result2;
    delete gray;
    delete result;
    delete image;*/

    return 0;
}