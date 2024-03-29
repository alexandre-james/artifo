#include "../lib/gif.h"
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
#include "filter/cartoon.hpp"
#include "filter/dot.hpp"
#include "filter/honeycomb.hpp"
#include "filter/tv.hpp"
#include "filter/glass.hpp"
#include "filter/engraving.hpp"

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
    int length = i - 1;
    while (i >= 0 && filename[i] != '/') {
        i--;
    }
    while (length >= 0 && filename[length] != '.') {
        length--;
    }
    strncpy(output, filename + i + 1, length - (i + 1));
    output[length - (i + 1)] = 0;
    return output;
}

int get_variable(int argc, char **argv, float &min, float &max, float &step) {
    for (int i = 3; i < argc; i++) {
        if (argv[i][0] == '[') {
            char number[100];
            int j = 1;
            int k = 0;
            while (argv[i][j] != ',')
                number[k++] = argv[i][j++];
            number[k] = 0;
            min = atof(number);
            k = 0;
            j++;
            while (argv[i][j] != ',')
                number[k++] = argv[i][j++];
            number[k] = 0;
            max = atof(number);
            k = 0;
            j++;
            while (argv[i][j] != ']')
                number[k++] = argv[i][j++];
            number[k] = 0;
            step = atof(number);

            return i;
        }
    }
    return -1;
}

rgb_image *filter(rgb_image *input, int argc, char **argv) {
    if (!strcmp(argv[1], "pixel")) {
        if (argc < 6) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo pixel <file_path/all> <height: int> <divisions: int> <outline: bool>\n");
            exit(1);
        }
        return pixel(input, atoi(argv[3]), atoi(argv[4]), strcmp(argv[5], "false") && strcmp(argv[5], "0"));
    }
    if (!strcmp(argv[1], "cartoon")) {
        if (argc < 5) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo cartoon <file_path/all> <nb_colors: int> <monochrom: bool>\n");
            exit(1);
        }
        return cartoon(input, atoi(argv[3]), strcmp(argv[4], "false") && strcmp(argv[4], "0"));
    }
    if (!strcmp(argv[1], "dot")) {
        if (argc < 5) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo dot <file_path/all> <width: int> <is_crop: bool>\n");
            exit(1);
        }
        return dot(input, atoi(argv[3]), strcmp(argv[4], "false") && strcmp(argv[4], "0"));
    }
    if (!strcmp(argv[1], "honeycomb")) {
        if (argc < 5) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo honeycomb <file_path/all> <width: int> <is_crop: bool>\n");
            exit(1);
        }
        return honeycomb(input, atoi(argv[3]), strcmp(argv[4], "false") && strcmp(argv[4], "0"));
    }
    if (!strcmp(argv[1], "tv")) {
        if (argc < 3) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo tv <file_path/all>\n");
            exit(1);
        }
        return tv(input);
    }
    if (!strcmp(argv[1], "glass")) {
        if (argc < 5) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo glass <file_path/all> <width: int> <grid: bool>\n");
            exit(1);
        }
        return glass(input, atoi(argv[3]), strcmp(argv[4], "false") && strcmp(argv[4], "0"));
    }
    if (!strcmp(argv[1], "engraving")) {
        if (argc < 3) {
            fprintf(stderr, "Invalid parameters\nformat: ./artifo engraving <file_path/all>\n");
            exit(1);
        }
        return engraving(input);
    }
    fprintf(stderr, "Invalid parameters: this filter doesn't exist\nformat: ./artifo <filter> <file_path/all> <args...>\n");
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Invalid parameters\nformat: ./artifo <filter> <file_path/all> <args...>\n");
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
            if (is_image(de->d_name)) {
                filenames[i] = (char *) malloc(100);
                strcpy(filenames[i++], de->d_name);
            }
        }
        
        closedir(dr);
    }
    else {
        nb_files = 1;
        filenames = (char **) malloc(sizeof(char *));
        filenames[0] = (char *) malloc(100);
        strcpy(filenames[0], argv[2]);
    }

    if (access("output", F_OK))
        mkdir("output", 0777);

    for (int i = 0; i < nb_files; i++) {
        char filename[100];
        char name[100];
        if (all) {
            strcpy(filename, "input/");
            strcat(filename, filenames[i]);
        }
        else {
            strcpy(filename, filenames[i]);
        }

        rgb_image *input = new rgb_image(filename);

        float min, max, step;
        int variable = get_variable(argc, argv, min, max, step);

        if (variable == -1) {
            rgb_image *output = filter(input, argc, argv);

            strcpy(filename, "output/");
            strcat(filename, get_name(name, filenames[i]));
            strcat(filename, ".png");
            output->save(filename);
            delete output;
        }
        else {
            char original[100];
            strcpy(original, argv[variable]);

            argv[variable] = (char*) to_string(min).c_str();
            rgb_image *output = filter(input, argc, argv);
            rgba_image *rgba_output = rgb_to_rgba(output);
            rgba_output->save("flex.png");
            strcpy(filename, "output/");
            strcat(filename, get_name(name, filenames[i]));
            printf("filename: %s\n", filename);
            strcat(filename, ".gif");

            GifWriter writer = {};
            GifBegin(&writer, filename, output->width, output->height, 50, 8, true);
            GifWriteFrame(&writer, rgba_output->pixels, output->width, output->height, 50, 8, true);

            delete output;
            delete rgba_output;

            for (float i = min + step; (min < max && i < max) || (min > max && i > max); i += step) {
                argv[variable] = (char *) to_string(i).c_str();
                output = filter(input, argc, argv);
                rgba_output = rgb_to_rgba(output);

                GifWriteFrame(&writer, rgba_output->pixels, output->width, output->height, 50, 8, true);

                delete output;
                delete rgba_output;
            }

            GifEnd( &writer );
            argv[variable] = original;
            free(filenames[i]);
        }

        delete input;
    }

    free(filenames);
    return 0;
}