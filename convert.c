#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "convert.h"
#include "koala.h"
#include "fade.h"
#include "utils.h"

void process1()
{
    printf("********** PROCESS1 **********\n");
    /* checkKla("output.kla"); */
    Koala *kla = loadKla("input.kla");
    Koala *to = loadKla("input.kla");
    optimize(kla);
    add_mask(kla);
    saveKla("output.kla", kla);
    fadeOut(kla, 1);
    free(kla);
    free(to);
}

void process2()
{
    printf("********** PROCESS2 **********\n");
    /* checkKla("output2.kla"); */
    Koala *kla = loadKla("output.kla");
    Koala *dest = getDestImg(kla);
    saveKla("output2.kla", dest);
    free(dest);
    free(kla);
}

Koala *getDestImg(Koala *kla)
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
            dest->color.color[i] = 0x01;
        }
        uint8_t c = 0;
        if (mask->mask2[i])
        {
            c = 0x40;
        }
        if (mask->mask1[i])
        {
            c = c | 0x01;
        }
        if (c)
        {
            dest->color.screen[i] = c;
        }
    }

    free(mask);

    return dest;
}

int main(void)
{
    process1();
    process2();
    return EXIT_SUCCESS;
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

void fadeIn(Koala *from, Koala *to)
{
}

void fadeOut(Koala *kla, uint8_t to)
{
    FILE *fout;
    if (!(fout = fopen("fadeout.asm", "w")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }

    Mask *mask = getMask(kla);
    Color color;
    Color buff;
    uint8_t color1, bcolor1 = 0x01;
    uint8_t color2, bcolor2 = 0x00;
    uint8_t color3, bcolor3 = 0x0c;

    memcpy(&buff, &(kla->color), sizeof(Color));
    fprintf(fout, "\n.section        code\n");
    for (int f = 1; f < 8; f++)
    {
        getTransitionTo(NEW_VIC, &(kla->color), &color, to, f, mask);
        color1 = getColorFade(NEW_VIC, 0x01, 0x01, f, 1);
        color2 = getColorFade(NEW_VIC, 0x00, 0x01, f, 1);
        color3 = getColorFade(NEW_VIC, 0x0c, 0x01, f, 1);

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
            if (color1 == c & color1 != bcolor1)
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
            if (color2 == c & color2 != bcolor2)
            {
                if (first)
                {
                    fprintf(fout, "                lda     #$%02x\n", c);
                    first = 0;
                }
                fprintf(fout, "                sta     $d025\n");
            }
            if (color3 == c & color3 != bcolor3)
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
