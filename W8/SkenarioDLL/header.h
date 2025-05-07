#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include "buku.h"

typedef struct PeminjamanAktif {
    Buku *buku;
    Peminjam *peminjam;
    struct PeminjamanAktif *next;
} PeminjamanAktif;

extern PeminjamanAktif *peminjamanList;

void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas prioritas);
void prosesPeminjaman(Buku *buku);
void prosesPengembalian(Buku *buku, const char nama[]);
void batalkanAntrean(Buku *buku, const char nama[]);
void lihatPeminjamanAktif();
void clearPeminjamanAktif();

// Menu
void displayMenu();
int getPilihan();
void inputString(char *buffer, size_t size, const char *prompt);
int inputInt(const char *prompt);

#endif
