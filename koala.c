#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#include "koala.h"
#include "utils.h"

Koala *loadKla(const char *filename)
{
    Koala *kla;
    if (!(kla = (Koala *) malloc(sizeof(Koala))))
    {
        die("Memory allocation error");
    }
    FILE *fin;
    if (!(fin = fopen(filename, "rb")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }
    int size = fread(kla, sizeof(Koala), 1, fin);
    if (size != 1 || ferror(fin))
    {
        die("%d %ld %ld \nError occured while reading file: %s", size, sizeof(Koala), sizeof(uint16_t), filename);
    }
    if (fclose(fin))
    {
        die("Error occured while closign file: %s", filename);
    }
    return kla;
}

void checkKla(const char *filename)
{
    struct stat buffer;
    if (!stat(filename, &buffer))
    {
        die("File %s already exists", filename);
    }
}

void saveKla(const char *filename, Koala *kla)
{
    checkKla(filename);

    FILE *fout;
    if (!(fout = fopen(filename, "wb")))
    {
        die("Error occured: %d, %s", errno, strerror(errno));
    }
    int size = fwrite(kla, sizeof(Koala), 1, fout);
    if (size != 1 || ferror(fout))
    {
        die("Error occured while writing file: %s", filename);
    }
    if (fclose(fout))
    {
        die("Error occured while writing file: %s", filename);
    }
}

void disposeKla(Koala *kla)
{
    free(kla);
}
