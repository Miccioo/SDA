#ifndef BUKU_H
#define BUKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjam.h"

typedef struct {
    char judul[50];
    int stok;
    Peminjam* antrianPeminjam;
} Buku;

#define BATAS_BUKU 100

extern Buku katalog[BATAS_BUKU];
extern int totalBuku;

void mulaiKatalog(void);
int katalogKosong(void);
Buku* alokasikanBuku(char namaBuku[], int stokAwal);
void insertBuku(char namaBuku[], int stokAwal);
void hapusBuku(char namaBuku[]);
Buku* findBuku(char namaBuku[]);
void printListBuku(void);
void clearListBuku(void);

#endif
