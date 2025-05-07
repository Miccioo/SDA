#include "header.h"

PeminjamanAktif *peminjamanList = NULL;

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas prioritas) {
    if (!buku) {
        return;
    }

    Peminjam *peminjamBaru = createPeminjam(nama, prioritas);
    if (!peminjamBaru) {
        printf("Gagal alokasi memori untuk peminjam.\n");
        return;
    }

    Peminjam *peminjamCurrent = buku->antrean;
    Peminjam *peminjamPrev = NULL;

    while (peminjamCurrent != NULL && peminjamCurrent->prioritas <= prioritas) {
        peminjamPrev = peminjamCurrent;
        peminjamCurrent = peminjamCurrent->next;
        if (peminjamCurrent != NULL && peminjamCurrent->next != NULL &&
            peminjamCurrent->next->prioritas > prioritas) {
            peminjamPrev = peminjamCurrent;
            peminjamCurrent = peminjamCurrent->next;
            break;
        }
    }

    peminjamBaru->next = peminjamCurrent;

    if (peminjamPrev == NULL) {
        buku->antrean = peminjamBaru;
    } else {
        peminjamPrev->next = peminjamBaru;
    }
}

void prosesPeminjaman(Buku *bukuPtr)
{
    if (!bukuPtr)
        return;

    if (!bukuPtr->antrean) {
        printf("Antrean di buku \"%s\" kosong.\n", bukuPtr->judul);
        return;
    }

    if (bukuPtr->stock <= 0) {
        printf("Stok buku \"%s\" habis.\n", bukuPtr->judul);
        return;
    }

    Peminjam *peminjamPtr = bukuPtr->antrean;
    bukuPtr->antrean = peminjamPtr->next;
    bukuPtr->stock--;

    PeminjamanAktif *peminjamanBaruPtr = (PeminjamanAktif *)malloc(sizeof(PeminjamanAktif));
    if (!peminjamanBaruPtr) {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");
        bukuPtr->antrean = peminjamPtr;
        bukuPtr->stock++;
        return;
    }

    peminjamanBaruPtr->buku = bukuPtr;
    peminjamanBaruPtr->peminjam = peminjamPtr;
    peminjamanBaruPtr->next = peminjamanList;
    peminjamanList = peminjamanBaruPtr;

    printf("Memproses peminjaman \"%s\" (prioritas %d) untuk buku \"%s\".\n",
           peminjamPtr->nama, peminjamPtr->prioritas, bukuPtr->judul);
}

void prosesPengembalian(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0') {
        return;
    }

    PeminjamanAktif *peminjamanCurrent = peminjamanList;
    PeminjamanAktif *peminjamanPrev = NULL;

    while (peminjamanCurrent != NULL &&
           !(strcmp(peminjamanCurrent->peminjam->nama, nama) == 0 &&
             peminjamanCurrent->buku == buku)) {
        peminjamanPrev = peminjamanCurrent;
        peminjamanCurrent = peminjamanCurrent->next;
    }

    if (peminjamanCurrent == NULL) {
        printf("Peminjaman aktif untuk \"%s\" pada buku \"%s\" tidak ditemukan.\n",
               nama, buku->judul);
        return;
    }

    if (peminjamanPrev == NULL) {
        peminjamanList = peminjamanCurrent->next;
    } else {
        peminjamanPrev->next = peminjamanCurrent->next;
    }

    buku->stock++;

    printf("Mengembalikan \"%s\" yang dipinjam oleh \"%s\".\n",
           peminjamanCurrent->buku->judul, peminjamanCurrent->peminjam->nama);

    free(peminjamanCurrent->peminjam);
    free(peminjamanCurrent);
}

void batalkanAntrean(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0') {
        return;
    }

    Peminjam *peminjamCurrent = buku->antrean;
    Peminjam *peminjamPrev = NULL;

    while (peminjamCurrent != NULL && strcmp(peminjamCurrent->nama, nama) != 0) {
        peminjamPrev = peminjamCurrent;
        peminjamCurrent = peminjamCurrent->next;
    }

    if (peminjamCurrent == NULL) {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n",
               nama, buku->judul);
        return;
    }

    if (peminjamPrev == NULL) {
        buku->antrean = peminjamCurrent->next;
    } else {
        peminjamPrev->next = peminjamCurrent->next;
    }

    free(peminjamCurrent);

    printf("Antrean peminjam \"%s\" untuk buku \"%s\" dibatalkan.\n",
           nama, buku->judul);
}

void lihatPeminjamanAktif() {
    if (peminjamanList == NULL) {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }

    printf("Daftar Peminjaman Aktif:\n");
    PeminjamanAktif *peminjamanCurrent = peminjamanList;
    while (peminjamanCurrent != NULL) {
        printf("- %s (prioritas %d) untuk buku \"%s\"\n",
               peminjamanCurrent->peminjam->nama,
               peminjamanCurrent->peminjam->prioritas,
               peminjamanCurrent->buku->judul);
        peminjamanCurrent = peminjamanCurrent->next;
    }
}

void clearPeminjamanAktif() {
    PeminjamanAktif *peminjamanCurrent = peminjamanList;
    while (peminjamanCurrent != NULL) {
        PeminjamanAktif *peminjamanTemp = peminjamanCurrent;
        peminjamanCurrent = peminjamanCurrent->next;
        free(peminjamanTemp->peminjam);
        free(peminjamanTemp);
    }
    peminjamanList = NULL;
}

void displayMenu() {
    printf("\n PERPUSTAKAAN(DLL):\n");
    printf("1. Insert Buku\n");
    printf("2. Display Buku\n");
    printf("3. Daftar yang Akan Meminjam\n");
    printf("4. Proses Pinjaman\n");
    printf("5. Batalkan Pinjaman\n");
    printf("6. Proses Pengembalian\n");
    printf("7. Lihat yang Sedang Meminjam\n");
    printf("0. Keluar\n");
}

int getPilihan() {
    int pilihan;
    printf("Pilihan Anda: ");
    scanf("%d", &pilihan);
    getchar();
    return pilihan;
}

void inputString(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int inputInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    getchar();
    return value;
}

