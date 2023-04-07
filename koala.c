#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#include "koala.h"
#include "utils.h"

Koala *loadKla(const char *filename)
{
    Koala *kla;
    if (!(kla = (Koala *)malloc(sizeof(Koala))))
    {
        die("Memory allocation error");
    }
    FILE *fin;
    if (!(fin = fopen(filename, "rb")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }
    int size = fread(kla, sizeof(Koala), 1, fin);
    if (size != 1 || ferror(fin))
    {
        die("%d %ld %ld \nError occured while reading file: %s", size, sizeof(Koala), sizeof(uint16_t), filename);
    }
    if (fclose(fin))
    {
        die("Error occured while closign file: %s", filename);
    }
    return kla;
}

void checkKla(const char *filename)
{
    struct stat buffer;
    if (!stat(filename, &buffer))
    {
        die("File %s already exists", filename);
    }
}

void saveKla(const char *filename, Koala *kla)
{
    /* checkKla(filename); */

    FILE *fout;
    if (!(fout = fopen(filename, "wb")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }
    int size = fwrite(kla, sizeof(Koala), 1, fout);
    if (size != 1 || ferror(fout))
    {
        die("Error occured while writing file: %s", filename);
    }
    if (fclose(fout))
    {
        die("Error occured while writing file: %s", filename);
    }
}

int check_bitmap(Mask *mask, int p, uint8_t v)
{
    int ret = 0;
    for (int i = p << 5; i < (p << 5) + 32; i++)
    {
        if (mask->bitmap[i] == v)
        {
            ret = 1;
            break;
        }
    }
    return ret;
}

void clear_bitmap(Mask *mask, int p, uint8_t v, uint8_t nv)
{
    int ret = 0;
    for (int i = p << 5; i < (p << 5) + 32; i++)
    {
        if (mask->bitmap[i] == v)
        {
            mask->bitmap[i] = nv;
        }
    }
}

void optimize(Koala *kla)
{
    Mask *mask = getMask(kla);

    uint8_t screen1[1000];
    uint8_t screen2[1000];

    for (int i = 0; i < 1000; i++)
    {
        screen1[i] = kla->color.screen[i] >> 4;
        screen2[i] = kla->color.screen[i] & 0x0f;
    }

    for (int i = 0; i < 1000; i++)
    {
        if (check_bitmap(mask, i, 1))
        {
            if (screen1[i] == kla->color.background)
            {
                printf("bitmap_screen1[%d] = 0\n", i);
                clear_bitmap(mask, i, 1, 0);
                screen1[i] = 0;
            }
        }
        else if (screen1[i])
        {
            printf("screen1[%d] = 0\n", i);
            screen1[i] = 0;
        }

        if (check_bitmap(mask, i, 2))
        {
            if (screen2[i] == kla->color.background)
            {
                printf("bitmap_screen2[%d] = 0\n", i);
                clear_bitmap(mask, i, 2, 0);
                screen2[i] = 0;
            }
        }
        else if (screen2[i])
        {
            printf("screen2[%d] = 0\n", i);
            screen2[i] = 0;
        }

        if (check_bitmap(mask, i, 3))
        {
            if (kla->color.color[i] == kla->color.background)
            {
                printf("bitmap_color[%d] = 0\n", i);
                clear_bitmap(mask, i, 3, 0);
                kla->color.color[i] = 0;
            }
        }
        else if (kla->color.color[i])
        {
            printf("color[%d] = 0\n", i);
            kla->color.color[i] = 0;
        }

        if (!check_bitmap(mask, i, 3) && check_bitmap(mask, i, 2))
        {
            printf("color[%d] <- screen2[%d]\n", i, i);
            kla->color.color[i] = screen2[i];
            clear_bitmap(mask, i, 2, 3);
            screen2[i] = 0;
        }

        if (!check_bitmap(mask, i, 3) && check_bitmap(mask, i, 1))
        {
            printf("color[%d] <- screen1[%d]\n", i, i);
            kla->color.color[i] = screen1[i];
            clear_bitmap(mask, i, 1, 3);
            screen1[i] = 0;
        }

        if (!check_bitmap(mask, i, 2) && check_bitmap(mask, i, 1))
        {
            printf("screen2[%d] <- screen1[%d]\n", i, i);
            screen2[i] = screen1[i];
            clear_bitmap(mask, i, 1, 2);
            screen1[i] = 0;
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        kla->color.screen[i] = (screen1[i] << 4) | screen2[i];
    }
    for (int i = 0; i < 32000; i++)
    {
        if (i & 3)
        {
            kla->bitmap[i >> 2] |= mask->bitmap[i] << ROTATE[i & 3];
        }
        else
        {
            kla->bitmap[i >> 2] = mask->bitmap[i] << ROTATE[i & 3];
        }
    }

    free(mask);
}

Mask *getMask(Koala *kla) {
    Mask *mask;
    if (!(mask = (Mask *)malloc(sizeof(Mask))))
    {
        die("Memory allocation error");
    }
    for (int i = 0; i < 32000; i++)
    {
        mask->bitmap[i] = (kla->bitmap[i >> 2] >> ROTATE[i & 3]) & 3;
    }
    for (int i = 0; i < 1000; i++)
    {
        mask->mask1[i] = check_bitmap(mask, i, 1);
        mask->mask2[i] = check_bitmap(mask, i, 2);
        mask->mask3[i] = check_bitmap(mask, i, 3);
    }
    return mask;
}
