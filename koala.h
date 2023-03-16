#ifndef KLA_H
#define KLA_H

#include <stdint.h>

typedef struct __attribute__ ((packed))
{
    uint16_t addr;
    uint8_t bitmap[8000];
    uint8_t screen[1000];
    uint8_t color[1000];
    uint8_t background; 
}  Koala;

Koala *loadKla(const char *filename);

void saveKla(const char *filename, Koala *kla);

void dispose(Koala *kla);

#endif
