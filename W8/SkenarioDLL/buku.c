#define _CRT_SECURE_NO_WARNINGS
#include "buku.h"

Buku *bukuHead = NULL;

void initList() {
    bukuHead = NULL;
}

int isListEmpty() {
    return bukuHead == NULL;
}

int isBukuExist(char judul[]) {
    Buku *bukuCurrent = bukuHead;
    while (bukuCurrent != NULL) {
        if (strcmp(bukuCurrent->judul, judul) == 0) {
            return 1;
        }
        bukuCurrent = bukuCurrent->next;
    }
    return 0;
}

Buku *createBuku(char judul[], int stock) {
    Buku *bukuBaru = (Buku *)malloc(sizeof(Buku));
    strcpy(bukuBaru->judul, judul);
    bukuBaru->stock = stock;
    bukuBaru->antrean = NULL;
    bukuBaru->next = NULL;
    return bukuBaru;
}

void insertBuku(char judul[], int stock) {
    if (isBukuExist(judul)) {
        printf("Buku dengan judul \"%s\" sudah ada!\n", judul);
        return;
    }

    Buku *bukuBaru = createBuku(judul, stock);

    if (isListEmpty()) {
        bukuHead = bukuBaru;
    } else {
        bukuBaru->next = bukuHead;
        bukuHead = bukuBaru;
    }
}

void deleteBuku(char judul[]) {
    if (isListEmpty()) {
        printf("List Kosong!\n");
        return;
    }

    Buku *bukuCurrent = bukuHead;
    Buku *bukuPrev = NULL;

    while (bukuCurrent != NULL && strcmp(bukuCurrent->judul, judul) != 0) {
        bukuPrev = bukuCurrent;
        bukuCurrent = bukuCurrent->next;
    }

    if (bukuCurrent == NULL) {
        printf("Buku tidak ditemukan!\n");
        return;
    }

    if (bukuPrev == NULL) {
        bukuHead = bukuCurrent->next;
    } else {
        bukuPrev->next = bukuCurrent->next;
    }

    free(bukuCurrent);
}

Buku *findBuku(char judul[]) {
    Buku *bukuCurrent = bukuHead;
    while (bukuCurrent != NULL) {
        if (strcmp(bukuCurrent->judul, judul) == 0) {
            return bukuCurrent;
        }
        bukuCurrent = bukuCurrent->next;
    }
    return NULL;
}

void displayAllBuku() {
    if (isListEmpty()) {
        printf("List Kosong!\n");
        return;
    }

    Buku *bukuCurrent = bukuHead;
    while (bukuCurrent != NULL) {
        printf("\nBuku: %s\nStock: %d\n", bukuCurrent->judul, bukuCurrent->stock);

        if (bukuCurrent->antrean != NULL) {
            printf("Daftar Antrean:\n");
            Peminjam *peminjamCurrent = bukuCurrent->antrean;
            while (peminjamCurrent != NULL) {
                printf("- %s (", peminjamCurrent->nama);
                switch (peminjamCurrent->prioritas) {
                    case DOSEN: printf("DOSEN"); break;
                    case MHS: printf("MAHASISWA"); break;
                    case UMUM: printf("UMUM"); break;
                }
                printf(")\n");
                peminjamCurrent = peminjamCurrent->next;
            }
        } else {
            printf("Tidak ada antrean\n");
        }
        printf("------------------------\n");
        bukuCurrent = bukuCurrent->next;
    }
}

void clearList() {
    while (!isListEmpty()) {
        Buku *bukuCurrent = bukuHead;
        clearPeminjam(bukuCurrent->antrean);
        deleteBuku(bukuHead->judul);
    }
}

