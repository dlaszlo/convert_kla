#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "convert.h"
#include "koala.h"
#include "fade.h"

int main(void)
{
    checkKla("output.kla");

    Koala *kla = loadKla("input.kla");

    optimize(kla);

    saveKla("output.kla", kla);

    fade(kla, 1);

    disposeKla(kla);

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
    uint8_t screen1[sizeof(kla->color.screen)];
    uint8_t screen2[sizeof(kla->color.screen)];

    for (int i = 0; i < sizeof(bitmap); i++)
    {
        bitmap[i] = (kla->bitmap[i >> 2] >> ROTATE[i & 3]) & 3;
    }
    for (int i = 0; i < sizeof(kla->color.screen); i++)
    {
        screen1[i] = kla->color.screen[i] >> 4;
        screen2[i] = kla->color.screen[i] & 0x0f;
    }

    for (int i = 0; i < sizeof(kla->color.screen); i++)
    {
        if (check_bitmap(bitmap, i, 1))
        {
            if (screen1[i] == kla->color.background)
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
            if (screen2[i] == kla->color.background)
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
            if (kla->color.color[i] == kla->color.background)
            {
                printf("bitmap_color[%d] = 0\n", i);
                clear_bitmap(bitmap, i, 3, 0);
                kla->color.color[i] = 0;
            }
        }
        else if (kla->color.color[i])
        {
            printf("color[%d] = 0\n", i);
            kla->color.color[i] = 0;
        }

        if (!check_bitmap(bitmap, i, 3) && check_bitmap(bitmap, i, 2))
        {
            printf("color[%d] <- screen2[%d]\n", i, i);
            kla->color.color[i] = screen2[i];
            clear_bitmap(bitmap, i, 2, 3);
            screen2[i] = 0;
        }

        if (!check_bitmap(bitmap, i, 3) && check_bitmap(bitmap, i, 1))
        {
            printf("color[%d] <- screen1[%d]\n", i, i);
            kla->color.color[i] = screen1[i];
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
        kla->color.screen[i] = (screen1[i] << 4) | screen2[i];
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

void fade(Koala *kla, uint8_t to)
{
    Color color;
    Color buff;
    uint8_t color1, bcolor1 = 0x01;
    uint8_t color2, bcolor2 = 0x00;
    uint8_t color3, bcolor3 = 0x0c;

    memcpy(&buff, &(kla->color), sizeof(Color));

    for (int f = 1; f < 8; f++)
    {
        getTransition(NEW_VIC, &(kla->color), &color, to, f);
        color1 = getColorFade(NEW_VIC, 0x01, 0x01, f, 1);
        color2 = getColorFade(NEW_VIC, 0x00, 0x01, f, 1);
        color3 = getColorFade(NEW_VIC, 0x0c, 0x01, f, 1);

        printf("fade_%d          .proc\n", f);

        for (int c = 0; c < 256; c++)
        {
            int first = 1;
            if (color.background == c && color.background != buff.background)
            {
                if (first)
                {
                    printf("                lda     #$%02x\n", c);
                    first = 0;
                }
                printf("                sta     $d020\n");
                printf("                sta     $d021\n");
            }
            if (color1 == c & color1 != bcolor1)
            {
                if (first)
                {
                    printf("                lda     #$%02x\n", c);
                    first = 0;
                }
                printf("                sta     $d027\n");
                printf("                sta     $d028\n");
                printf("                sta     $d029\n");
                printf("                sta     $d02a\n");
                printf("                sta     $d02b\n");
                printf("                sta     $d02c\n");
                printf("                sta     $d02d\n");
                printf("                sta     $d02e\n");
            }
            if (color2 == c & color2 != bcolor2)
            {
                if (first)
                {
                    printf("                lda     #$%02x\n", c);
                    first = 0;
                }
                printf("                sta     $d025\n");
            }
            if (color3 == c & color3 != bcolor3)
            {
                if (first)
                {
                    printf("                lda     #$%02x\n", c);
                    first = 0;
                }
                printf("                sta     $d026\n");
            }
            for (int i = 0; i < sizeof(color.color); i++)
            {
                if (c != 0)
                {
                    if (color.color[i] == c && color.color[i] != buff.color[i])
                    {
                        if (first)
                        {
                            printf("                lda     #$%02x\n", c);
                            first = 0;
                        }
                        printf("                sta     COLOR + %d\n", i);
                    }
                    if (color.screen[i] == c && color.screen[i] != buff.screen[i])
                    {
                        if (first)
                        {
                            printf("                lda     #$%02x\n", c);
                            first = 0;
                        }
                        printf("                sta     SCREEN + %d\n", i);
                    }
                }
            }
        }
        printf("                rts\n");
        printf("                .pend\n");

        memcpy(&buff, &color, sizeof(Color));
        bcolor1 = color1;
        bcolor2 = color2;
        bcolor3 = color3;
    }
}
