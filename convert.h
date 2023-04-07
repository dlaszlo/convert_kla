#ifndef CONVERT_H
#define CONVERT_H
#include <stdint.h>
#include "koala.h"

void add_mask(Koala *kla);
void optimize(Koala *kla);
void fadeOut(Koala *kla, uint8_t to);
Koala *getDestImg(Koala *kla);
void fadeIn(Koala *from, Koala *to);

#endif