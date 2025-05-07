#ifndef PEMINJAM_H
#define PEMINJAM_H

#define MAX_NAMA 50

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DOSEN = 1,
    MHS = 2,
    UMUM = 3
} Prioritas;

typedef struct Peminjam {
    char nama[MAX_NAMA];
    Prioritas prioritas;
    struct Peminjam *next;
} Peminjam;

Peminjam *createPeminjam(const char nama[], Prioritas pr);
void clearPeminjam(Peminjam *head);

#endif

