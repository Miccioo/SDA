#ifndef PEMINJAM_H
#define PEMINJAM_H

typedef enum {
    DOSEN = 1,
    MHS   = 2,
    UMUM  = 3
} Prioritas;

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buku.h"

typedef struct Peminjam {
    char nama[50];
    Prioritas prioritas;
    struct Peminjam *nextPeminjam;
    struct Buku *nextBuku;
} Peminjam;

Peminjam* createPeminjam(const char nama[], Prioritas pr);

void clearPeminjam(Peminjam *head);

#endif

