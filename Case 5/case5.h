#ifndef CASE5_H
#define CASE5_H
#include "linked.h"

#define MAX_KOTA 10

// Deklarasi kota, extern adalah deklarasi variabel yang definisinya ada di file lain. yaitu di main.c
typedef struct {
    char namaKota[20]; // Tambahkan field nama kota
    List daftarOrang;
} Kota;

extern Kota A[MAX_KOTA]; 

boolean kotaEmpty(Kota L);

// Konstraktor
void createKota(Kota *L, int index);

// Destruktor
void deleteKota(Kota *L, int index);

// Penambahan orang yang ada di kota
void tambahOrangFirst(Kota *L, int index, char *nama);
void tambahOrangLast(Kota *L, int index, char *nama);

// Pengurangan orang yang ada di kota
void hapusOrangByNama(Kota *L, int index, char *nama);
void hapusOrangFirst(Kota *L, int index);
void hapusOrangLast(Kota *L, int index);

// Tampilan semua kota dan semua nama orang yang ada di kota
void printKota(Kota *L);
void printOrang(Kota *L, int index);

// Interaktif tampilan
void tampilMennu();
#endif
