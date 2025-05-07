#ifndef HEADER_H
#define HEADER_H

#include "listAntrian.h"

typedef struct PeminjamanAktif {
    Buku *buku;
    Peminjam *peminjam;
    struct PeminjamanAktif *next;
} PeminjamanAktif;

extern PeminjamanAktif *PeminjamanList;

void setUjungJadiBuku(listAntrean *list, Buku *buku);
void initialAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr);
void prosesPeminjaman(Buku *buku);
void prosesPengembalian(Buku *buku, const char nama[]);
void batalkanAntrean(Buku *buku, const char nama[]);
void lihatPeminjamanAktif();
void clearPeminjamanAktif();
void displayAllBukuAndAntrean();

// Menu
void displayMenu();
int getPilihan();
void inputString(char *buffer, size_t size, const char *prompt);
int inputInt(const char *prompt);

#endif
