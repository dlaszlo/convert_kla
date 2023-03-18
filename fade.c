#include <stdio.h>
#include <stdlib.h>
#include "fade.h"
#include "koala.h"

const uint8_t FADE_NEW_VIC[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x0d, 0x03, 0x0c, 0x04, 0x02, 0x09, 0x00},
    {0x02, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x0c, 0x04, 0x02, 0x09, 0x00, 0x00, 0x00},
    {0x04, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x05, 0x08, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00},
    {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x07, 0x0f, 0x05, 0x08, 0x02, 0x09, 0x00, 0x00},
    {0x08, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0a, 0x08, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00},
    {0x0b, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0c, 0x04, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00},
    {0x0d, 0x03, 0x0c, 0x04, 0x02, 0x09, 0x00, 0x00},
    {0x0e, 0x04, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00},
    {0x0f, 0x05, 0x08, 0x02, 0x09, 0x00, 0x00, 0x00},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x03, 0x0d, 0x01},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x02, 0x08, 0x0a, 0x0f, 0x07, 0x01, 0x01, 0x01},
    {0x03, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x04, 0x0c, 0x03, 0x0d, 0x01, 0x01, 0x01, 0x01},
    {0x05, 0x03, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x06, 0x0b, 0x04, 0x0c, 0x03, 0x0d, 0x01, 0x01},
    {0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x08, 0x0a, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x01},
    {0x09, 0x02, 0x08, 0x0a, 0x0f, 0x07, 0x01, 0x01},
    {0x0a, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0b, 0x04, 0x0c, 0x03, 0x0d, 0x01, 0x01, 0x01},
    {0x0c, 0x03, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0e, 0x03, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0f, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x00, 0x09, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x01, 0x07, 0x0f, 0x0a, 0x08, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x03, 0x0c, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x05, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x06, 0x0b, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x07, 0x0f, 0x0a, 0x08, 0x02, 0x02, 0x02, 0x02},
    {0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x09, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0a, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0b, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0c, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0d, 0x03, 0x0c, 0x04, 0x02, 0x02, 0x02, 0x02},
    {0x0e, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0f, 0x0a, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x03, 0x03, 0x03},
    {0x01, 0x0d, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x02, 0x04, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x04, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x06, 0x0b, 0x04, 0x0c, 0x03, 0x03, 0x03, 0x03},
    {0x07, 0x0f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x08, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x09, 0x02, 0x04, 0x0c, 0x03, 0x03, 0x03, 0x03},
    {0x0a, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0b, 0x04, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0c, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0d, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0e, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x00, 0x06, 0x0b, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x01, 0x0d, 0x03, 0x0c, 0x04, 0x04, 0x04, 0x04},
    {0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x03, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x05, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x06, 0x0b, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x07, 0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x09, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0a, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0b, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0d, 0x03, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x05, 0x05, 0x05},
    {0x01, 0x0d, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x02, 0x08, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x04, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x06, 0x0b, 0x04, 0x0c, 0x05, 0x05, 0x05, 0x05},
    {0x07, 0x0f, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x08, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x09, 0x02, 0x08, 0x0c, 0x05, 0x05, 0x05, 0x05},
    {0x0a, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0b, 0x04, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0d, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0e, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0f, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x01, 0x0d, 0x03, 0x0e, 0x04, 0x0b, 0x06, 0x06},
    {0x02, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x03, 0x0e, 0x04, 0x0b, 0x06, 0x06, 0x06, 0x06},
    {0x04, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x05, 0x08, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x07, 0x0f, 0x0c, 0x04, 0x0b, 0x06, 0x06, 0x06},
    {0x08, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x09, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0a, 0x08, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0c, 0x04, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0d, 0x03, 0x0e, 0x04, 0x0b, 0x06, 0x06, 0x06},
    {0x0e, 0x04, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0f, 0x0c, 0x04, 0x0b, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x09, 0x02, 0x08, 0x0a, 0x0f, 0x07, 0x07},
    {0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x02, 0x08, 0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07},
    {0x03, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x04, 0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x05, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x06, 0x0b, 0x04, 0x0a, 0x0f, 0x07, 0x07, 0x07},
    {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x08, 0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x09, 0x02, 0x08, 0x0a, 0x0f, 0x07, 0x07, 0x07},
    {0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0b, 0x04, 0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07},
    {0x0c, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0d, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0e, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x00, 0x09, 0x02, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x01, 0x07, 0x0f, 0x0c, 0x08, 0x08, 0x08, 0x08},
    {0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x03, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x05, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x06, 0x0b, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x07, 0x0f, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x09, 0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0b, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0d, 0x03, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0e, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0f, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x00, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x01, 0x07, 0x0f, 0x0c, 0x08, 0x02, 0x09, 0x09},
    {0x02, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x03, 0x0c, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09},
    {0x04, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x05, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x06, 0x0b, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x07, 0x0f, 0x0c, 0x08, 0x02, 0x09, 0x09, 0x09},
    {0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0a, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0b, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0c, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0d, 0x03, 0x0c, 0x08, 0x02, 0x09, 0x09, 0x09},
    {0x0e, 0x04, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0f, 0x0c, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09},
    {0x00, 0x09, 0x02, 0x04, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x01, 0x07, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x02, 0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x03, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x05, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x06, 0x0b, 0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x07, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x09, 0x02, 0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0b, 0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0d, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0e, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x00, 0x06, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x01, 0x0d, 0x03, 0x0e, 0x04, 0x0b, 0x0b, 0x0b},
    {0x02, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x03, 0x0e, 0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x05, 0x08, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x06, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x07, 0x0f, 0x0c, 0x04, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x08, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0a, 0x08, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0c, 0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0d, 0x03, 0x0e, 0x04, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0e, 0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0f, 0x0c, 0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x01, 0x0d, 0x03, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x02, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x03, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x05, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x06, 0x0b, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x07, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x09, 0x02, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0a, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0b, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0d, 0x03, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x00, 0x09, 0x02, 0x08, 0x0c, 0x0f, 0x0d, 0x0d},
    {0x01, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x02, 0x08, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x03, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x04, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x05, 0x03, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x06, 0x0b, 0x04, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d},
    {0x07, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x08, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x09, 0x02, 0x08, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d},
    {0x0a, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0b, 0x04, 0x0c, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0c, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0e, 0x03, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x0e, 0x0e, 0x0e},
    {0x01, 0x0d, 0x03, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x02, 0x04, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x03, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x04, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x05, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x06, 0x0b, 0x04, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x07, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x08, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x09, 0x02, 0x04, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0a, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0b, 0x04, 0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0d, 0x03, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x00, 0x06, 0x0b, 0x04, 0x0c, 0x0f, 0x0f, 0x0f},
    {0x01, 0x0d, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x02, 0x08, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x03, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x04, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x05, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x06, 0x0b, 0x04, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x08, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x09, 0x02, 0x04, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0b, 0x04, 0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0d, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f}};

const uint8_t FADE_OLD_VIC[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x07, 0x03, 0x0e, 0x04, 0x02, 0x0b, 0x00},
    {0x02, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x0e, 0x04, 0x02, 0x0b, 0x00, 0x00, 0x00},
    {0x04, 0x02, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x05, 0x08, 0x09, 0x0b, 0x00, 0x00, 0x00, 0x00},
    {0x06, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x07, 0x03, 0x0e, 0x04, 0x02, 0x0b, 0x00, 0x00},
    {0x08, 0x09, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x09, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0a, 0x04, 0x02, 0x0b, 0x00, 0x00, 0x00, 0x00},
    {0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0c, 0x06, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x0d, 0x0f, 0x0a, 0x04, 0x02, 0x0b, 0x00, 0x00},
    {0x0e, 0x04, 0x02, 0x0b, 0x00, 0x00, 0x00, 0x00},
    {0x0f, 0x0a, 0x04, 0x02, 0x0b, 0x00, 0x00, 0x00},
    {0x00, 0x0b, 0x02, 0x04, 0x0e, 0x03, 0x0d, 0x01},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x02, 0x04, 0x0e, 0x03, 0x0d, 0x01, 0x01, 0x01},
    {0x03, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x04, 0x0e, 0x03, 0x0d, 0x01, 0x01, 0x01, 0x01},
    {0x05, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x06, 0x02, 0x04, 0x0e, 0x03, 0x0d, 0x01, 0x01},
    {0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x08, 0x05, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x01},
    {0x09, 0x08, 0x05, 0x0f, 0x07, 0x01, 0x01, 0x01},
    {0x0a, 0x0f, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0b, 0x02, 0x04, 0x0e, 0x03, 0x0d, 0x01, 0x01},
    {0x0c, 0x08, 0x05, 0x0f, 0x07, 0x01, 0x01, 0x01},
    {0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0e, 0x03, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x0f, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x00, 0x0b, 0x09, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x01, 0x0d, 0x0e, 0x04, 0x02, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x03, 0x0e, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x05, 0x0c, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x06, 0x09, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x07, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x09, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0a, 0x08, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0b, 0x09, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0c, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0d, 0x0e, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0e, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x0f, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x00, 0x0b, 0x06, 0x0e, 0x03, 0x03, 0x03, 0x03},
    {0x01, 0x0d, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x02, 0x04, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x04, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x06, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x08, 0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x09, 0x04, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0a, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0b, 0x06, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0c, 0x0e, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0d, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0e, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x0f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x00, 0x0b, 0x02, 0x0c, 0x04, 0x04, 0x04, 0x04},
    {0x01, 0x07, 0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04},
    {0x02, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x03, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x06, 0x02, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x07, 0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x09, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0a, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0b, 0x02, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0d, 0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x0f, 0x0a, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x00, 0x0b, 0x09, 0x0c, 0x05, 0x05, 0x05, 0x05},
    {0x01, 0x0d, 0x0f, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x02, 0x08, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x06, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x07, 0x0f, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x08, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x09, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0a, 0x08, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0b, 0x09, 0x0c, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0c, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0d, 0x0f, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0e, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x0f, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x00, 0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x01, 0x0d, 0x03, 0x0e, 0x06, 0x06, 0x06, 0x06},
    {0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x03, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x04, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x05, 0x04, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x07, 0x0f, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x08, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x09, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0a, 0x08, 0x09, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0b, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0c, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0d, 0x03, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x0f, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x0b, 0x0c, 0x08, 0x0f, 0x07, 0x07, 0x07},
    {0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x02, 0x08, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x04, 0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x05, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x06, 0x0e, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x08, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x09, 0x08, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0a, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0b, 0x0c, 0x08, 0x0f, 0x07, 0x07, 0x07, 0x07},
    {0x0c, 0x08, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0d, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0e, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x00, 0x0b, 0x09, 0x0c, 0x08, 0x08, 0x08, 0x08},
    {0x01, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x03, 0x0a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x05, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x06, 0x09, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x07, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x09, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0a, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0b, 0x09, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0d, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x00, 0x0b, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x01, 0x07, 0x0a, 0x08, 0x02, 0x09, 0x09, 0x09},
    {0x02, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x03, 0x05, 0x0c, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x04, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x05, 0x0c, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x07, 0x0a, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09},
    {0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0a, 0x08, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0b, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0c, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0d, 0x0f, 0x05, 0x0c, 0x09, 0x09, 0x09, 0x09},
    {0x0e, 0x0c, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x0f, 0x05, 0x0c, 0x09, 0x09, 0x09, 0x09, 0x09},
    {0x00, 0x0b, 0x09, 0x08, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x01, 0x07, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x02, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x03, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x05, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x06, 0x09, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x07, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x09, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0b, 0x09, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0c, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0d, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0e, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x0f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a},
    {0x00, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x01, 0x0d, 0x05, 0x08, 0x09, 0x0b, 0x0b, 0x0b},
    {0x02, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x03, 0x05, 0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x04, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x05, 0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x06, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x07, 0x0a, 0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0a, 0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0d, 0x05, 0x08, 0x09, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0e, 0x06, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x0f, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b},
    {0x00, 0x0b, 0x09, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x01, 0x07, 0x0f, 0x04, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x02, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x03, 0x0f, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x05, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x06, 0x09, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x07, 0x0f, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x09, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0a, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0b, 0x09, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0d, 0x0f, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x0f, 0x04, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c},
    {0x00, 0x0b, 0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x01, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x02, 0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x03, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x04, 0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x06, 0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x07, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x08, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x09, 0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0a, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0b, 0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0c, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0e, 0x05, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x0f, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d},
    {0x00, 0x0b, 0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x01, 0x0d, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x02, 0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x03, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x05, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x06, 0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x07, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x08, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x09, 0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0a, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0b, 0x04, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0c, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0d, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e},
    {0x00, 0x0b, 0x09, 0x08, 0x0a, 0x0f, 0x0f, 0x0f},
    {0x01, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x02, 0x04, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x03, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x04, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x05, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x06, 0x09, 0x08, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x08, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x09, 0x08, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0a, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0b, 0x09, 0x08, 0x0a, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0c, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0d, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f},
    {0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f}};

const uint8_t FADE_CHAR_MODE[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x07, 0x03, 0x05, 0x04, 0x02, 0x06, 0x00},
    {0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x05, 0x04, 0x02, 0x06, 0x00, 0x00, 0x00},
    {0x04, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x05, 0x04, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00},
    {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x07, 0x03, 0x05, 0x04, 0x02, 0x06, 0x00, 0x00},
    {0x00, 0x06, 0x02, 0x04, 0x05, 0x03, 0x07, 0x01},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x02, 0x04, 0x05, 0x03, 0x07, 0x01, 0x01, 0x01},
    {0x03, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x04, 0x05, 0x03, 0x07, 0x01, 0x01, 0x01, 0x01},
    {0x05, 0x03, 0x07, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x06, 0x02, 0x04, 0x05, 0x03, 0x07, 0x01, 0x01},
    {0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    {0x00, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x01, 0x07, 0x03, 0x05, 0x04, 0x02, 0x02, 0x02},
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x03, 0x05, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x05, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x07, 0x03, 0x05, 0x04, 0x02, 0x02, 0x02, 0x02},
    {0x00, 0x06, 0x02, 0x04, 0x05, 0x03, 0x03, 0x03},
    {0x01, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x02, 0x04, 0x05, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x04, 0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x06, 0x02, 0x04, 0x05, 0x03, 0x03, 0x03, 0x03},
    {0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x00, 0x06, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x01, 0x07, 0x03, 0x05, 0x04, 0x04, 0x04, 0x04},
    {0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x03, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x06, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x07, 0x03, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
    {0x00, 0x06, 0x02, 0x04, 0x05, 0x05, 0x05, 0x05},
    {0x01, 0x07, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x02, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x06, 0x02, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x07, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05},
    {0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x01, 0x07, 0x03, 0x05, 0x04, 0x02, 0x06, 0x06},
    {0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x03, 0x05, 0x04, 0x02, 0x06, 0x06, 0x06, 0x06},
    {0x04, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x05, 0x04, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x07, 0x03, 0x05, 0x04, 0x02, 0x06, 0x06, 0x06},
    {0x00, 0x06, 0x02, 0x04, 0x05, 0x03, 0x07, 0x07},
    {0x01, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x02, 0x04, 0x05, 0x03, 0x07, 0x07, 0x07, 0x07},
    {0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x04, 0x05, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x05, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07},
    {0x06, 0x02, 0x04, 0x05, 0x03, 0x07, 0x07, 0x07},
    {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07}};

uint8_t getColorFade(enum FADE_TABLE fade_table, uint8_t fr, uint8_t to, uint8_t idx)
{
    if (idx < 0 || idx > 7)
    {
        printf("Invalid index. Table: %d; From: %d; To: %d; Index: %d", fade_table, fr, to, idx);
        exit(EXIT_FAILURE);
    }

    uint8_t ret = fr == 0 ? 0 : 255;

    if (ret)
    {
        if (fade_table == NEW_VIC)
        {
            for (int i = 0; i < 256; i++)
            {
                if (FADE_NEW_VIC[i][0] == fr && FADE_NEW_VIC[i][7] == to)
                {
                    ret = FADE_NEW_VIC[i][idx];
                    break;
                }
            }
        }
        else if (fade_table == OLD_VIC)
        {
            for (int i = 0; i < 256; i++)
            {
                if (FADE_OLD_VIC[i][0] == fr && FADE_OLD_VIC[i][7] == to)
                {
                    ret = FADE_OLD_VIC[i][idx];
                    break;
                }
            }
        }
        else if (fade_table == CHAR_MODE)
        {
            for (int i = 0; i < 128; i++)
            {
                if (FADE_CHAR_MODE[i][0] == fr && FADE_CHAR_MODE[i][7] == to)
                {
                    ret = FADE_CHAR_MODE[i][idx];
                    break;
                }
            }
        }
        else
        {
            printf("Invalid fade table. Table: %d; From: %d; To: %d; Index: %d", fade_table, fr, to, idx);
            exit(EXIT_FAILURE);
        }

        if (ret > 15)
        {
            printf("Color not found. Table: %d; From: %d; To: %d; Index: %d", fade_table, fr, to, idx);
            exit(EXIT_FAILURE);
        }
    }

    return ret;
}

uint8_t getScreenFade(enum FADE_TABLE fade_table, uint8_t fr, uint8_t to, uint8_t idx)
{
    uint8_t c1 = getColorFade(fade_table, (fr >> 4) & 0x0f, to, idx);
    uint8_t c2 = getColorFade(fade_table, fr & 0x0f, to, idx);
    return (c1 << 4) | c2;
}

void getTransition(enum FADE_TABLE fade_table, Color *from, Color *dest, uint8_t to, uint8_t idx)
{
    for (int i = 0; i < sizeof(from->color) / sizeof(from->color[0]); i++)
    {
        dest->color[i] = getColorFade(fade_table, from->color[i], to, idx);
        dest->screen[i] = getScreenFade(fade_table, from->screen[i], to, idx);
    }
}
