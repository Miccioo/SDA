#ifndef PEMINJAM_H
#define PEMINJAM_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DOSEN = 1,
    MHS = 2,
    UMUM = 3
} LevelPrioritas;

typedef struct Peminjam {
    char nama[50];
    LevelPrioritas prioritas;
    struct Peminjam* next;
} Peminjam;

Peminjam* buatPeminjam(const char nama[], LevelPrioritas level);
void bersihkanAntrian(Peminjam* kepala);

#endif
