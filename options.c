#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "options.h"
#include "utils.h"

void usage()
{

    printf("Usage:\n");
    printf("./convert [parameters]\n");
    printf("Parameters:\n");
    printf("  --help                                  Help\n");
    printf("  --fade_in or --fade_out                 Required. Task: generate fade in or fade out.\n");
    printf("  --input         <input.kla>             Required. Input KLA file.\n");
    printf("  --sprite_from   <sprite_color_from.txt> Optional. TXT file containing the sprite colors.\n");
    printf("                                                    The file should contain 3 two-digit hexadecimal numbers representing\n");
    printf("                                                    the three sprite colors.\n");
    printf("  --sprite_to     <sprite_color_to.txt>   Optional. TXT file containing the sprite colors.\n");
    printf("                                                    The file should contain 3 two-digit hexadecimal numbers representing\n");
    printf("                                                    the three sprite colors.\n");
    printf("  --output        <output.kla>            Required. Output KLA file.\n");
    printf("  --source_output <fade.asm>              Required. Generated output source code file.\n");
    printf("  --color         <color_code>            Required. Fade in or out color code in two-digit hexadecimal format.\n");
}

void parse_options(int argc, char *argv[], Options *options)
{
    memset(options, 0, sizeof(Options));

    options->color = 255;
    static int mode;
    static struct option long_options[] = {
        {"help", no_argument, &mode, MODE_HELP},
        {"fade_in", no_argument, &mode, MODE_FADE_IN},
        {"fade_out", no_argument, &mode, MODE_FADE_OUT},
        {"input", required_argument, NULL, 'i'},
        {"sprite_from", required_argument, NULL, 'f'},
        {"sprite_to", required_argument, NULL, 't'},
        {"output", required_argument, NULL, 'o'},
        {"source_output", required_argument, NULL, 's'},
        {"color", required_argument, NULL, 'c'},
        {NULL, 0, NULL, 0}};

    while (1)
    {
        int option_index = 0;
        int c = getopt_long(argc, argv, "-:i:f:t:o:s:c:", long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            break;

        case 'i':
            if (strlen(optarg) > MAX_FILENAME_LEN)
            {
                usage();
                die("Error: input file name too long.");
            }
            strncpy(options->input_filename, optarg, MAX_FILENAME_LEN);
            break;

        case 'f':
            if (strlen(optarg) > MAX_FILENAME_LEN)
            {
                usage();
                die("Error: sprite from file name too long.");
            }
            strncpy(options->sprite_colors_from, optarg, MAX_FILENAME_LEN);
            break;

        case 't':
            if (strlen(optarg) > MAX_FILENAME_LEN)
            {
                usage();
                die("Error: sprite to file name too long.");
            }
            strncpy(options->sprite_colors_to, optarg, MAX_FILENAME_LEN);
            break;

        case 'o':
            if (strlen(optarg) > MAX_FILENAME_LEN)
            {
                usage();
                die("Error: output file name too long.");
            }
            strncpy(options->output_filename, optarg, MAX_FILENAME_LEN);
            break;

        case 's':
            if (strlen(optarg) > MAX_FILENAME_LEN)
            {
                usage();
                die("Error: source code file name too long.");
            }
            strncpy(options->output_source, optarg, MAX_FILENAME_LEN);
            break;

        case 'c':
            int temp;
            if (strlen(optarg) != 2 || sscanf(optarg, "%x", &temp) != 1 || temp < 0 || temp > 15)
            {
                usage();
                die("Error: invalid color value: %s", optarg);
            }
            options->color = (uint8_t)temp;
            break;

        case '?':
            usage();
            die("Unknown option %c", optopt);
            break;

        case ':':
            usage();
            die("Missing option argument for %c", optopt);
            break;

        default:
            break;
        }
    }

    options->mode = mode;

    if (!options->mode || options->mode == MODE_HELP)
    {
        usage();
        exit(EXIT_SUCCESS);
    }

    if (options->mode != MODE_FADE_IN && options->mode != MODE_FADE_OUT)
    {
        usage();
        die("The program must be used in fade_in or fade_out mode.");
    }

    if (!strlen(options->input_filename))
    {
        usage();
        die("Missing parameter: input");
    }

    if (!strlen(options->output_filename))
    {
        usage();
        die("Missing parameter: output");
    }

    if (!strlen(options->output_source))
    {
        usage();
        die("Missing parameter: source_output");
    }

    if ((!strlen(options->sprite_colors_from) && strlen(options->sprite_colors_to)) ||
        (strlen(options->sprite_colors_from) && !strlen(options->sprite_colors_to)))
    {
        usage();
        die("Both sprite_from and sprite_to parameters are required when using either of them.");
    }

    if (options->color > 15)
    {
        usage();
        die("Missing parameter: color");
    }
}
