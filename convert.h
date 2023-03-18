#ifndef CONVERT_H
#define CONVERT_H
#include <stdint.h>
#include "koala.h"

int check_bitmap(uint8_t *bitmap, int p, uint8_t v);
void clear_bitmap(uint8_t *bitmap, int p, uint8_t v, uint8_t nv);
void optimize(Koala *kla);
void fade(Koala *kla, uint8_t to);

const uint8_t ROTATE[4] = {6, 4, 2, 0};

#endif