#ifndef KLA_H
#define KLA_H

#include <stdint.h>

typedef struct __attribute__((packed))
{
    uint8_t screen[1000];
    uint8_t color[1000];
    uint8_t background;
} Color;

typedef struct __attribute__((packed))
{
    uint16_t addr;
    uint8_t bitmap[8000];
    Color color;
} Koala;

typedef struct __attribute__((packed))
{
    uint8_t bitmap[32000];
    uint8_t mask1[1000];
    uint8_t mask2[1000];
    uint8_t mask3[1000];
    uint8_t background;
} Mask;

typedef struct __attribute__((packed))
{
    uint8_t color1;
    uint8_t color2;
    uint8_t color3;
} SpriteColor;

const uint8_t ROTATE[4] = {6, 4, 2, 0};

void checkKla(const char *filename);

Koala *loadKla(const char *filename);

void saveKla(const char *filename, Koala *kla);

int check_bitmap(Mask *mask, int p, uint8_t v);

void clear_bitmap(Mask *mask, int p, uint8_t v, uint8_t nv);

Mask *getMask(Koala *kla);

void optimize(Koala *kla);

#endif
