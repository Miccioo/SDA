#include "peminjam.h"

Peminjam* createPeminjam(const char nama[], Prioritas pr) {
    if (!nama || nama[0] == '\0') {
        printf("Nama peminjam tidak valid\n");
        return NULL;
    }

    if (pr < DOSEN || pr > UMUM) {
        printf("Prioritas peminjam tidak valid\n");
        return NULL;
    }

    Peminjam *peminjamBaru = (Peminjam *) malloc(sizeof(Peminjam));
    if (peminjamBaru) {
        strncpy(peminjamBaru->nama, nama, sizeof(peminjamBaru->nama) - 1);
        peminjamBaru->nama[sizeof(peminjamBaru->nama) - 1] = '\0';

        peminjamBaru->prioritas = pr;
        peminjamBaru->nextPeminjam = NULL;
        peminjamBaru->nextBuku = NULL;
    }

    return peminjamBaru;
}

void clearPeminjam(Peminjam *head) {
    Peminjam *current = head;
    while (current) {
        Peminjam *hapus = current;
        current = current->nextPeminjam;
        free(hapus);
    }
}

