#include "peminjam.h"

Peminjam* buatPeminjam(const char nama[], LevelPrioritas level) {
    if (!nama || nama[0] == '\0') return NULL;
    if (level < DOSEN || level > UMUM) return NULL;

    Peminjam* baru = malloc(sizeof(Peminjam));
    if (baru) {
        strncpy(baru->nama, nama, sizeof(baru->nama) - 1);
        baru->nama[sizeof(baru->nama) - 1] = '\0';
        baru->prioritas = level;
        baru->next = NULL;
    }
    return baru;
}

void bersihkanAntrian(Peminjam* kepala) {
    while (kepala) {
        Peminjam* sementara = kepala;
        kepala = kepala->next;
        free(sementara);
    }
}

