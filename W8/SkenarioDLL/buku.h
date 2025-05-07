#ifndef BUKU_H
#define BUKU_H

#define MAX_JUDUL 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjam.h"

typedef struct Buku {
    char judul[MAX_JUDUL];
    int stock;
    Peminjam *antrean;
    struct Buku *next;
} Buku;

// Linked list operations
extern Buku *bukuHead;
void initList();
int isListEmpty();
int isBukuExist(char judul[]);
Buku *createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku *findBuku(char judul[]);
void displayAllBuku();
void clearList();

#endif

