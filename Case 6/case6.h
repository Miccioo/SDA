#ifndef CASE6_H
#define CASE6_H
#include "linked.h"
#include "case5.h"
#define MAX_KOTA 10

typedef struct tElmtKota *addressKota;
typedef struct tElmtKota {
    Kota info;
    addressKota next;
} ElmtKota;

typedef struct {
    addressKota First;
} ListKota;

extern Kota A[MAX_KOTA]; 

/* Prototype */
boolean ListKotaEmpty(ListKota L);

/* Membuat list kota kosong */
void CreateListKota(ListKota *L);

/* Alokasi elemen kota */
addressKota AlokasiKota(Kota X);

/* Dealokasi elemen kota */
void DeAlokasiKota(addressKota P);

/* Menambahkan kota baru ke list */
void AddKota(ListKota *L, char *namaKota);

/* Menambahkan orang baru ke kota */
void AddOrangToKota(ListKota *L, char *namaKota, char *namaOrang);

/* Menghapus orang dari kota */
void RemoveOrangFromKota(ListKota *L, char *namaKota, char *namaOrang);

/* Menambahkan elemen kota ke list */
void InsertFirstKota(ListKota *L, addressKota P);
void InsertLastKota(ListKota *L, addressKota P);
void InsertAfterKota(ListKota *L, addressKota P, addressKota Prec);

/* Menghapus elemen kota dari list */
void DeleteFirstKota(ListKota *L, addressKota *P);
void DeleteLastKota(ListKota *L, addressKota *P);
void DeleteAfterKota(ListKota *L, addressKota *P, addressKota Prec);
void DeleteKotaByName(ListKota *L, char *namaKota);

/* Mencari elemen kota berdasarkan nama */
addressKota SearchKota(ListKota L, char *namaKota);

/* Menampilkan daftar orang di kota tertentu */
void PrintPeopleInCity(ListKota L, char *namaKota);

/* Meanmpilkan semuanya */
void PrintAllCitiesAndPeople(ListKota L);

void displayMenu();


#endif
