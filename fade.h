#ifndef FADE_H
#define FADE_H

#include <stdint.h>

extern const uint8_t FADE_NEW_VIC[][8];
extern const uint8_t FADE_OLD_VIC[][8];
extern const uint8_t FADE_CHAR_MODE[][8];

enum FADE_TABLE
{
    NEW_VIC,
    OLD_VIC,
    CHAR_MODE
};

uint8_t getColorFade(enum FADE_TABLE fade_table, uint8_t fr, uint8_t to, uint8_t idx);
uint8_t getScreenFade(enum FADE_TABLE fade_table, uint8_t fr, uint8_t to, uint8_t idx);

#endif