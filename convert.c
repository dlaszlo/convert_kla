#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "koala.h"
#include "fade.h"

int check_bitmap(uint8_t *bitmap, int p, uint8_t v);
void clear_bitmap(uint8_t *bitmap, int p, uint8_t v, uint8_t nv);
void optimize(Koala *kla);

const uint8_t ROTATE[4] = {6, 4, 2, 0};

int main(void)
{

    Koala *kla = loadKla("input.kla");

    optimize(kla);

    saveKla("output.kla", kla);

    dispose(kla);

    return EXIT_SUCCESS;
}

int check_bitmap(uint8_t *bitmap, int p, uint8_t v)
{
    int ret = 0;
    for (int i = p << 5; i < (p << 5) + 32; i++)
    {
        if (bitmap[i] == v)
        {
            ret = 1;
            break;
        }
    }
    return ret;
}

void clear_bitmap(uint8_t *bitmap, int p, uint8_t v, uint8_t nv)
{
    int ret = 0;
    for (int i = p << 5; i < (p << 5) + 32; i++)
    {
        if (bitmap[i] == v)
        {
            bitmap[i] = nv;
        }
    }
}

void optimize(Koala *kla)
{
    uint8_t bitmap[sizeof(kla->bitmap) * 4];
    uint8_t screen1[sizeof(kla->screen)];
    uint8_t screen2[sizeof(kla->screen)];

    for (int i = 0; i < sizeof(bitmap); i++)
    {
        bitmap[i] = (kla->bitmap[i >> 2] >> ROTATE[i & 3]) & 3;
    }
    for (int i = 0; i < sizeof(kla->screen); i++)
    {
        screen1[i] = kla->screen[i] >> 4;
        screen2[i] = kla->screen[i] & 0x0f;
    }

    for (int i = 0; i < sizeof(kla->screen); i++)
    {
        if (check_bitmap(bitmap, i, 1))
        {
            if (screen1[i] == kla->background)
            {
                printf("bitmap_screen1[%d] = 0\n", i);
                clear_bitmap(bitmap, i, 1, 0);
                screen1[i] = 0;
            }
        }
        else if (screen1[i])
        {
            printf("screen1[%d] = 0\n", i);
            screen1[i] = 0;
        }

        if (check_bitmap(bitmap, i, 2))
        {
            if (screen2[i] == kla->background)
            {
                printf("bitmap_screen2[%d] = 0\n", i);
                clear_bitmap(bitmap, i, 2, 0);
                screen2[i] = 0;
            }
        }
        else if (screen2[i])
        {
            printf("screen2[%d] = 0\n", i);
            screen2[i] = 0;
        }

        if (check_bitmap(bitmap, i, 3))
        {
            if (kla->color[i] == kla->background)
            {
                printf("bitmap_color[%d] = 0\n", i);
                clear_bitmap(bitmap, i, 3, 0);
                kla->color[i] = 0;
            }
        }
        else if (kla->color[i])
        {
            printf("color[%d] = 0\n", i);
            kla->color[i] = 0;
        }

        if (!check_bitmap(bitmap, i, 3) && check_bitmap(bitmap, i, 2))
        {
            printf("color[%d] <- screen2[%d]\n", i, i);
            kla->color[i] = screen2[i];
            clear_bitmap(bitmap, i, 2, 3);
            screen2[i] = 0;
        }

        if (!check_bitmap(bitmap, i, 3) && check_bitmap(bitmap, i, 1))
        {
            printf("color[%d] <- screen1[%d]\n", i, i);
            kla->color[i] = screen1[i];
            clear_bitmap(bitmap, i, 1, 3);
            screen1[i] = 0;
        }

        if (!check_bitmap(bitmap, i, 2) && check_bitmap(bitmap, i, 1))
        {
            printf("screen2[%d] <- screen1[%d]\n", i, i);
            screen2[i] = screen1[i];
            clear_bitmap(bitmap, i, 1, 2);
            screen1[i] = 0;
        }
    }

    for (int i = 0; i < sizeof(screen1); i++)
    {
        kla->screen[i] = (screen1[i] << 4) | screen2[i];
    }
    for (int i = 0; i < sizeof(bitmap); i++)
    {
        if (i & 3)
        {
            kla->bitmap[i >> 2] |= bitmap[i] << ROTATE[i & 3];
        }
        else
        {
            kla->bitmap[i >> 2] = bitmap[i] << ROTATE[i & 3];
        }
    }
}
