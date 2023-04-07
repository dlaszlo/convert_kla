#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdint.h>

#define MAX_FILENAME_LEN 256

#define MODE_HELP 1000
#define MODE_FADE_IN 1001
#define MODE_FADE_OUT 1002


typedef struct
{
    char input_filename[MAX_FILENAME_LEN];
    char sprite_colors_from[MAX_FILENAME_LEN];
    char sprite_colors_to[MAX_FILENAME_LEN];
    char output_filename[MAX_FILENAME_LEN];
    char output_source[MAX_FILENAME_LEN];
    int mode;
    uint8_t color;
} Options;

void parse_options(int argc, char *argv[], Options *options);

#endif