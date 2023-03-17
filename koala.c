#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "koala.h"

Koala *loadKla(const char *filename)
{
    Koala *kla;
    if (!(kla = malloc(sizeof(Koala))))
    {
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    FILE *fin;
    if (!(fin = fopen(filename, "rb")))
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    int size = fread(kla, sizeof(Koala), 1, fin);
    if (size != 1 || ferror(fin))
    {
        printf("%d %d %d \n", size, sizeof(Koala), sizeof(uint16_t));
        printf("Error occured while reading file: %s", filename);
        exit(EXIT_FAILURE);
    }
    if (fclose(fin))
    {
        printf("Error occured while reading file: %s", filename);
        exit(EXIT_FAILURE);
    }
    return kla;
}

void checkKla(const char *filename)
{
    struct stat buffer;
    if (!stat(filename, &buffer))
    {
        printf("File %s already exists", filename);
        exit(EXIT_FAILURE);
    }
}

void saveKla(const char *filename, Koala *kla)
{
    checkKla(filename);

    FILE *fout;
    if (!(fout = fopen(filename, "wb")))
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    int size = fwrite(kla, sizeof(Koala), 1, fout);
    if (size != 1 || ferror(fout))
    {
        printf("Error occured while writing file: %s", filename);
        exit(EXIT_FAILURE);
    }
    if (fclose(fout))
    {
        printf("Error occured while writing file: %s", filename);
        exit(EXIT_FAILURE);
    }
}

void disposeKla(Koala *kla)
{
    free(kla);
}
