#include "peminjam.h"

Peminjam *createPeminjam(const char nama[], Prioritas pr) {
    if (!nama || nama[0] == '\0') {
        return NULL;
    }
    if (pr < DOSEN || pr > UMUM) {
        return NULL;
    }

    Peminjam *peminjamBaru = malloc(sizeof(Peminjam));
    if (peminjamBaru) {
        strncpy(peminjamBaru->nama, nama, sizeof(peminjamBaru->nama) - 1);
        peminjamBaru->nama[sizeof(peminjamBaru->nama) - 1] = '\0';
        peminjamBaru->prioritas = pr;
        peminjamBaru->next = NULL;
    }
    return peminjamBaru;
}

void clearPeminjam(Peminjam *head) {
    while (head != NULL) {
        Peminjam *peminjamTemp = head;
        head = head->next;
        free(peminjamTemp);
    }
}

