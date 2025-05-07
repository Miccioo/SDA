#ifndef LIST_ANTRIAN_H
#define LIST_ANTRIAN_H

#include "peminjam.h"

typedef struct listAntrean {
    struct Peminjam *antrean;
    struct listAntrean *next;
} listAntrean;

extern listAntrean *HEAD_ListAntrean;

int isListAntreanEmpty();
void insertListAntrean(listAntrean *newList);
listAntrean *getListAntreanByBuku(Buku *buku);
listAntrean *getListAntreanByBukuNull(Buku *buku);
listAntrean *createListAntrean();
void clearListAntrean();

#endif

