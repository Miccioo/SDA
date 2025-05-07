#ifndef BUKU_H
#define BUKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

typedef struct Buku {
    char judul[MAX_LENGTH];
    int stock;
    struct Buku *next;
} Buku;

extern Buku *HEAD_Buku;

void initList();
int isListBukuEmpty();
Buku *createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku *findBuku(char judul[]);
void clearListBuku();

#endif

