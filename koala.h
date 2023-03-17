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

void checkKla(const char *filename);

Koala *loadKla(const char *filename);

void saveKla(const char *filename, Koala *kla);

void disposeKla(Koala *kla);

#endif
