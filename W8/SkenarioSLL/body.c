#include "header.h"

PeminjamanAktif *PeminjamanList = NULL;

void setUjungJadiBuku(listAntrean *list, Buku *buku) {
    Peminjam *p = list->antrean;
    if (!p) return;

    while (p->nextPeminjam != NULL) {
        p = p->nextPeminjam;
    }
    p->nextBuku = buku;
}

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr) {
    if (!buku || !nama || nama[0] == '\0') return;

    listAntrean *list = getListAntreanByBuku(buku);
    Peminjam *baru = createPeminjam(nama, pr);

    if (list->antrean == NULL) {
        baru->nextBuku = buku;
        list->antrean = baru;
        return;
    }

    Peminjam *curr = list->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && curr->prioritas <= pr) {
        prev = curr;
        curr = curr->nextPeminjam;
        if (curr->nextBuku == buku) {
            prev = curr;
            curr->nextBuku = NULL;
            curr = NULL;
        }
    }

    baru->nextPeminjam = curr;

    if (prev == NULL) {
        list->antrean = baru;
    } else {
        prev->nextPeminjam = baru;
    }

    setUjungJadiBuku(list, buku);
}

void prosesPeminjaman(Buku *buku) {
    if (!buku) return;

    listAntrean *list = getListAntreanByBukuNull(buku);
    if (!list || list->antrean == NULL) {
        printf("Tidak ada antrean peminjaman untuk buku ini!\n");
        return;
    }

    if (buku->stock <= 0) {
        printf("Stock buku \"%s\" habis.\n", buku->judul);
        return;
    }

    Peminjam *p = list->antrean;
    Peminjam *next = p->nextPeminjam;

    list->antrean = next;
    p->nextPeminjam = NULL;
    buku->stock--;

    PeminjamanAktif *baru = malloc(sizeof(PeminjamanAktif));
    if (!baru) {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");
        p->nextPeminjam = next;
        list->antrean = p;
        buku->stock++;
        return;
    }

    baru->buku = buku;
    baru->peminjam = p;
    baru->next = PeminjamanList;
    PeminjamanList = baru;

    printf("Memproses peminjaman \"%s\" (prioritas %d) untuk buku \"%s\".\n",
           p->nama, p->prioritas, buku->judul);
}

void prosesPengembalian(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0') return;

    PeminjamanAktif *curr = PeminjamanList;
    PeminjamanAktif *prev = NULL;

    while (curr != NULL &&
           !(strcmp(curr->peminjam->nama, nama) == 0 && curr->buku == buku)) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Peminjaman aktif untuk \"%s\" pada buku \"%s\" tidak ditemukan.\n",
               nama, buku->judul);
        return;
    }

    if (!prev) {
        PeminjamanList = curr->next;
    } else {
        prev->next = curr->next;
    }

    buku->stock++;

    printf("Mengembalikan \"%s\" yang dipinjam oleh \"%s\".\n",
           curr->buku->judul, curr->peminjam->nama);

    free(curr->peminjam);
    free(curr);
}

void batalkanAntrean(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0') return;

    listAntrean *list = getListAntreanByBukuNull(buku);
    if (!list || list->antrean == NULL) {
        printf("List kosong!");
        return;
    }

    Peminjam *curr = list->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0) {
        prev = curr;
        curr = curr->nextPeminjam;
    }

    if (!curr) {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n",
               nama, buku->judul);
        return;
    }

    if (!prev) {
        list->antrean = curr->nextPeminjam;
    } else {
        prev->nextPeminjam = curr->nextPeminjam;
    }

    free(curr);
    printf("Antrean peminjam \"%s\" untuk buku \"%s\" dibatalkan.\n",
           nama, buku->judul);
}

void lihatPeminjamanAktif() {
    if (!PeminjamanList) {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }

    printf("Daftar Peminjaman Aktif:\n");
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL) {
        printf("- %s (prioritas %d) untuk buku \"%s\"\n",
               curr->peminjam->nama, curr->peminjam->prioritas, curr->buku->judul);
        curr = curr->next;
    }
}

void clearPeminjamanAktif() {
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL) {
        PeminjamanAktif *tmp = curr;
        curr = curr->next;
        free(tmp->peminjam);
        free(tmp);
    }
    PeminjamanList = NULL;
}

void displayAllBukuAndAntrean() {
    if (isListBukuEmpty()) {
        printf("List Buku kosong!\n");
        return;
    }

    Buku *b = HEAD_Buku;
    while (b != NULL) {
        printf("\nBuku: %s\nStock: %d\n", b->judul, b->stock);
        printf("------------------------\n");

        listAntrean *list = getListAntreanByBukuNull(b);
        if (list && list->antrean != NULL) {
            Peminjam *p = list->antrean;
            while (p != NULL) {
                printf("Nama: %s, Prioritas: %d (%s)\n",
                       p->nama,
                       p->prioritas,
                       p->prioritas == 1 ? "Dosen" :
                       p->prioritas == 2 ? "Mahasiswa" : "Umum");
                p = p->nextPeminjam;
            }
        } else {
            printf("belum ada yang meminjam buku ini\n");
        }

        printf("------------------------\n");
        b = b->next;
    }
}

void displayMenu() {
    printf("\n PERPUSTAKAAN 1:\n");
    printf("1. Insert Buku\n");
    printf("2. Display Buku (dan Antrean)\n");
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

