#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include "utils.h"

void die(const char *msg, ...)
{
    va_list params;
    va_start(params, msg);
    vfprintf(stderr, msg, params);
    va_end(params);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}
