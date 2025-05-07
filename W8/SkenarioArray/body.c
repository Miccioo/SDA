#include "header.h"

DaftarPeminjaman *daftarPinjamAktif = NULL;

void tambahAntreanPeminjam(Buku* b, const char* nama, LevelPrioritas prioritas) {
    if (!b) return;
    Peminjam* baru = buatPeminjam(nama, prioritas);
    if (!baru) return;

    Peminjam* curr = b->antrianPeminjam;
    Peminjam* prev = NULL;

    while (curr && curr->prioritas <= prioritas) {
        prev = curr;
        curr = curr->next;
    }

    baru->next = curr;
    if (!prev) b->antrianPeminjam = baru;
    else prev->next = baru;
}


void jalankanPeminjaman(Buku* b) {
    if (!b || !b->antrianPeminjam || b->stok <= 0) return;

    Peminjam* p = b->antrianPeminjam;
    b->antrianPeminjam = p->next;
    b->stok--;

    DaftarPeminjaman* baru = malloc(sizeof(DaftarPeminjaman));
    if (!baru) return;
    baru->buku = b;
    baru->peminjam = p;
    baru->next = daftarPinjamAktif;
    daftarPinjamAktif = baru;

    printf("Peminjaman oleh %s (Prioritas %d) untuk buku '%s' berhasil.\n", p->nama, p->prioritas, b->judul);
}

void kembalikanBuku(Buku* b, const char* nama) {
    if (!b || !nama) return;
    DaftarPeminjaman* curr = daftarPinjamAktif, *prev = NULL;

    while (curr) {
        if (curr->buku == b && strcmp(curr->peminjam->nama, nama) == 0) break;
        prev = curr;
        curr = curr->next;
    }

    if (!curr) return;
    if (!prev) daftarPinjamAktif = curr->next;
    else prev->next = curr->next;

    printf("Buku '%s' dikembalikan oleh %s.\n", b->judul, curr->peminjam->nama);
    b->stok++;
    free(curr->peminjam);
    free(curr);
}

void hapusAntreanPeminjam(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0') return;

    Peminjam *curr = buku->antrianPeminjam;
    Peminjam *prev = NULL;

    // Cari peminjam dalam antrean
    while (curr && strcmp(curr->nama, nama) != 0) {
        prev = curr;
        curr = curr->next;
    }

    // Jika peminjam tidak ditemukan
    if (!curr) {
        printf("Peminjam \"%s\" tidak ditemukan pada antrean buku \"%s\".\n", nama, buku->judul);
        return;
    }

    // Jika peminjam adalah elemen pertama dalam antrean
    if (!prev) {
        buku->antrianPeminjam = curr->next;
    } else {
        prev->next = curr->next;
    }

    // Hapus peminjam dari memori
    free(curr);
    printf("Peminjam \"%s\" dibatalkan dari antrean buku \"%s\".\n", nama, buku->judul);
}


void tampilkanPeminjamanAktif(void) {
    DaftarPeminjaman* curr = daftarPinjamAktif;
    if (!curr) {
        printf("Tidak ada peminjaman aktif saat ini.\n");
        return;
    }
    while (curr) {
          printf("- %s (P%d) meminjam '%s'\n", curr->peminjam->nama, curr->peminjam->prioritas, curr->buku->judul);
        curr = curr->next;
    }
}

void tampilkanSeluruhBukuDanAntrean()
{
    if (totalBuku == 0) {
        printf("Tidak ada buku tersedia saat ini.\n");
        return;
    }

    for (int i = 0; i < totalBuku; i++) {
        printf("[%d] \"%s\" - Stok: %d\n", i + 1, katalog[i].judul, katalog[i].stok);
        Peminjam *q = katalog[i].antrianPeminjam;

        if (!q) {
            printf("    Antrean kosong\n");
        } else {
            printf("    Daftar Antrean:\n");
            int urut = 1;
            while (q) {
                printf("      %d. %s (P%d)\n", urut++, q->nama, q->prioritas);
                q = q->next;
            }
        }
    }
}

void hapusSeluruhPeminjamanAktif() {
    DaftarPeminjaman *temp = daftarPinjamAktif;
    while (temp) {
        DaftarPeminjaman *del = temp;
        temp = temp->next;
        free(del->peminjam);
        free(del);
    }
    daftarPinjamAktif = NULL;
}

void displayMenu() {
    printf("\n PERPUSTAKAAN (Array 1):\n");
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

