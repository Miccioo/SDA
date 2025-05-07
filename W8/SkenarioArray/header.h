#ifndef HEADER_H
#define HEADER_H

#include "buku.h"

typedef struct DaftarPeminjaman {
    Buku *buku;
    Peminjam *peminjam;
    struct DaftarPeminjaman *next;
} DaftarPeminjaman;

extern DaftarPeminjaman *daftarPinjamAktif;

void tambahAntreanPeminjam(Buku *targetBuku, const char peminjamNama[], LevelPrioritas prioritas);
void jalankanPeminjaman(Buku *b);
void kembalikanBuku(Buku *b, const char nama[]);
void hapusAntreanPeminjam(Buku *b, const char nama[]);
void tampilkanPeminjamanAktif();
void tampilkanSeluruhBukuDanAntrean();
void hapusSeluruhPeminjamanAktif();

// Menu
void displayMenu();
int getPilihan();
void inputString(char *buffer, size_t size, const char *prompt);
int inputInt(const char *prompt);

#endif
