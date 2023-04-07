#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "convert.h"
#include "koala.h"
#include "fade.h"
#include "utils.h"
#include "options.h"

void fade_out(const char *input_file, const char *sprite_from, const char *sprite_to, const char *output_file, const char *output_source, uint8_t color)
{
    /* checkKla(output_file); */
    Koala *kla = loadKla(input_file);
    optimize(kla);
    add_mask(kla);
    saveKla(output_file, kla);
    Koala *dest = getDestImg(kla, color);

    if (sprite_from && strlen(sprite_from) && sprite_to && strlen(sprite_to))
    {
        SpriteColor spriteColorFrom;
        SpriteColor spriteColorTo;
        read_sprinte_colors(sprite_from, &spriteColorFrom);
        read_sprinte_colors(sprite_to, &spriteColorTo);
        fade(kla, dest, &spriteColorFrom, &spriteColorTo, output_source);
    }
    else
    {
        fade(kla, dest, NULL, NULL, output_source);
    }

    free(dest);
    free(kla);
}

void fade_in(const char *input_file, const char *sprite_from, const char *sprite_to, const char *output_file, const char *output_source, uint8_t color)
{
    /* checkKla(output_file); */
    Koala *kla = loadKla(input_file);
    optimize(kla);
    add_mask(kla);
    Koala *dest = getDestImg(kla, color);
    saveKla(output_file, dest);

    if (sprite_from && strlen(sprite_from) && sprite_to && strlen(sprite_to))
    {
        SpriteColor spriteColorFrom;
        SpriteColor spriteColorTo;
        read_sprinte_colors(sprite_from, &spriteColorFrom);
        read_sprinte_colors(sprite_to, &spriteColorTo);
        fade(dest, kla, &spriteColorFrom, &spriteColorTo, output_source);
    }
    else
    {
        fade(dest, kla, NULL, NULL, output_source);
    }

    free(dest);
    free(kla);
}

int main(int argc, char *argv[])
{
    Options options;

    parse_options(argc, argv, &options);

    if (options.mode == MODE_FADE_IN)
    {
        fade_in(options.input_filename, options.sprite_colors_from, options.sprite_colors_to, options.output_filename, options.output_source, options.color);
    }
    else if (options.mode == MODE_FADE_OUT)
    {
        fade_out(options.input_filename, options.sprite_colors_from, options.sprite_colors_to, options.output_filename, options.output_source, options.color);
    }
    else
    {
        die("Invalid mode.");
    }
    return EXIT_SUCCESS;
}

Koala *getDestImg(Koala *kla, uint8_t color)
{
    Koala *dest;
    if (!(dest = (Koala *)malloc(sizeof(Koala))))
    {
        die("Memory allocation error");
    }
    memcpy(dest, kla, sizeof(Koala));
    dest->color.background = 0x01;

    Mask *mask = getMask(kla);

    for (int i = 0; i < 1000; i += 1)
    {
        if (mask->mask3[i])
        {
            dest->color.color[i] = color & 0x0f;
        }
        uint8_t c = 0;
        if (mask->mask2[i])
        {
            c = color & 0x0f;
        }
        if (mask->mask1[i])
        {
            c = c | ((color & 0x0f) << 4);
        }
        if (c)
        {
            dest->color.screen[i] = c;
        }
    }

    free(mask);

    return dest;
}

void add_mask(Koala *kla)
{
    for (int i = 40 * 23 * 8; i < 40 * 25 * 8; i++)
    {
        kla->bitmap[i] = 0xff;
    }
    for (int i = 40 * 23; i < 40 * 25; i++)
    {
        kla->color.color[i] = 0;
        kla->color.screen[i] = 0;
    }
}

void read_sprinte_colors(const char *filename, SpriteColor *sprite_color)
{
    FILE *fin;
    if (!(fin = fopen(filename, "r")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }
    int temp1, temp2, temp3;
    int ret = fscanf(fin, "%x %x %x", &temp1, &temp2, &temp3);
    if (ret != 3)
    {
        die("Error occured, invalid file format: %s", filename);
    }
    sprite_color->color1 = (uint8_t)temp1;
    sprite_color->color2 = (uint8_t)temp2;
    sprite_color->color3 = (uint8_t)temp3;
    fclose(fin);
}

void fade(Koala *kla, Koala *dest, SpriteColor *spriteColorFrom, SpriteColor *spriteColorTo, const char *filename)
{
    FILE *fout;
    if (!(fout = fopen(filename, "w")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }

    Mask *mask = getMask(dest);
    Color color;
    Color buff;
    uint8_t color1, bcolor1 = spriteColorFrom && spriteColorTo ? spriteColorFrom->color1 : 0;
    uint8_t color2, bcolor2 = spriteColorFrom && spriteColorTo ? spriteColorFrom->color2 : 0;
    uint8_t color3, bcolor3 = spriteColorFrom && spriteColorTo ? spriteColorFrom->color3 : 0;

    memcpy(&buff, &(kla->color), sizeof(Color));
    fprintf(fout, "\n.section        code\n");
    for (int f = 1; f < 8; f++)
    {
        getTransition(NEW_VIC, &(kla->color), &color, &(dest->color), f, mask);
        if (spriteColorFrom && spriteColorTo)
        {
            color1 = getColorFade(NEW_VIC, spriteColorFrom->color1, spriteColorTo->color1, f, 1);
            color2 = getColorFade(NEW_VIC, spriteColorFrom->color2, spriteColorTo->color2, f, 1);
            color3 = getColorFade(NEW_VIC, spriteColorFrom->color3, spriteColorTo->color3, f, 1);
        }

        fprintf(fout, "\nfade_%d          .proc\n", f);

        for (int c = 0; c < 256; c++)
        {
            int first = 1;
            if (color.background == c && color.background != buff.background)
            {
                if (first)
                {
                    fprintf(fout, "                lda     #$%02x\n", c);
                    first = 0;
                }
                fprintf(fout, "                sta     $d020\n");
                fprintf(fout, "                sta     $d021\n");
            }
            if (spriteColorFrom && spriteColorTo && color1 == c & color1 != bcolor1)
            {
                if (first)
                {
                    fprintf(fout, "                lda     #$%02x\n", c);
                    first = 0;
                }
                fprintf(fout, "                sta     $d027\n");
                fprintf(fout, "                sta     $d028\n");
                fprintf(fout, "                sta     $d029\n");
                fprintf(fout, "                sta     $d02a\n");
                fprintf(fout, "                sta     $d02b\n");
                fprintf(fout, "                sta     $d02c\n");
                fprintf(fout, "                sta     $d02d\n");
                fprintf(fout, "                sta     $d02e\n");
            }
            if (spriteColorFrom && spriteColorTo && color2 == c & color2 != bcolor2)
            {
                if (first)
                {
                    fprintf(fout, "                lda     #$%02x\n", c);
                    first = 0;
                }
                fprintf(fout, "                sta     $d025\n");
            }
            if (spriteColorFrom && spriteColorTo && color3 == c & color3 != bcolor3)
            {
                if (first)
                {
                    fprintf(fout, "                lda     #$%02x\n", c);
                    first = 0;
                }
                fprintf(fout, "                sta     $d026\n");
            }
            for (int i = 0; i < sizeof(color.color); i++)
            {
                if (color.color[i] == c && color.color[i] != buff.color[i])
                {
                    if (first)
                    {
                        fprintf(fout, "                lda     #$%02x\n", c);
                        first = 0;
                    }
                    fprintf(fout, "                sta     COLOR + %d\n", i);
                }
                if (color.screen[i] == c && color.screen[i] != buff.screen[i])
                {
                    if (first)
                    {
                        fprintf(fout, "                lda     #$%02x\n", c);
                        first = 0;
                    }
                    fprintf(fout, "                sta     SCREEN + %d\n", i);
                }
            }
        }
        fprintf(fout, "                rts\n");
        fprintf(fout, "                .pend\n");

        memcpy(&buff, &color, sizeof(Color));
        bcolor1 = color1;
        bcolor2 = color2;
        bcolor3 = color3;
    }
    fprintf(fout, "\n                .send\n");
    free(mask);
    fclose(fout);
}
