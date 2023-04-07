#ifndef CONVERT_H
#define CONVERT_H
#include <stdint.h>
#include "koala.h"

void add_mask(Koala *kla);
void optimize(Koala *kla);
Koala *getDestImg(Koala *kla, uint8_t color);
void fade(Koala *kla, Koala *dest, SpriteColor *spriteColorFrom, SpriteColor *spriteColorTo, const char *filename);
void read_sprinte_colors(const char *filename, SpriteColor *sprite_color);

#endif