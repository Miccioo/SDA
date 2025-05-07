#include "buku.h"

#define BATAS_BUKU 100

Buku katalog[BATAS_BUKU];
int totalBuku = 0;

void mulaiKatalog(void) {
    totalBuku = 0;
}

int katalogKosong(void) {
    return totalBuku == 0;
}

Buku* alokasikanBuku(char namaBuku[], int stokAwal) {
    Buku* baru = malloc(sizeof(Buku));
    if (!baru) {
        puts("Memori gagal dialokasikan untuk buku.");
        return NULL;
    }
    strncpy(baru->judul, namaBuku, sizeof(baru->judul) - 1);
    baru->judul[sizeof(baru->judul) - 1] = '\0';
    baru->stok = stokAwal;
    baru->antrianPeminjam = NULL;
    return baru;
}

void insertBuku(char namaBuku[], int stokAwal) {
    if (totalBuku >= BATAS_BUKU) {
        puts("Kapasitas buku telah penuh.");
        return;
    }
    strncpy(katalog[totalBuku].judul, namaBuku, sizeof(katalog[totalBuku].judul) - 1);
    katalog[totalBuku].judul[sizeof(katalog[totalBuku].judul) - 1] = '\0';
    katalog[totalBuku].stok = stokAwal;
    katalog[totalBuku].antrianPeminjam = NULL;
    totalBuku++;
}

void hapusBuku(char namaBuku[]) {
    int posisi = -1;
    for (int i = 0; i < totalBuku; ++i) {
        if (strcmp(katalog[i].judul, namaBuku) == 0) {
            posisi = i;
            break;
        }
    }
    if (posisi == -1) {
        printf("Buku \"%s\" tidak ditemukan!\n", namaBuku);
        return;
    }
    bersihkanAntrian(katalog[posisi].antrianPeminjam);
    for (int j = posisi; j < totalBuku - 1; ++j) {
        katalog[j] = katalog[j + 1];
    }
    totalBuku--;
}

Buku* findBuku(char namaBuku[]) {
    for (int i = 0; i < totalBuku; ++i) {
        if (strcmp(katalog[i].judul, namaBuku) == 0) {
            return &katalog[i];
        }
    }
    return NULL;
}

void printListBuku(void) {
    if (katalogKosong()) {
        puts("Katalog masih kosong.");
        return;
    }
    puts("Isi Katalog Buku:");
    for (int i = 0; i < totalBuku; ++i) {
        printf("[%d] %s - Tersedia: %d\n", i + 1, katalog[i].judul, katalog[i].stok);
    }
}

void clearListBuku(void) {
    for (int i = 0; i < totalBuku; ++i) {
        bersihkanAntrian(katalog[i].antrianPeminjam);
    }
    totalBuku = 0;
}

