#include <stdio.h>
#include <stdlib.h>
#include "listAntrian.h"
#include "buku.h"
#include "peminjam.h"

listAntrean *HEAD_ListAntrean = NULL;

int isListAntreanEmpty() {
    return HEAD_ListAntrean == NULL;
}

listAntrean *createListAntrean() {
    listAntrean *newList = malloc(sizeof(listAntrean));
    if (newList == NULL) {
        return NULL;
    }
    newList->antrean = NULL;
    newList->next = NULL;
    return newList;
}

void insertListAntrean(listAntrean *newList) {
    if (!newList) return;
    newList->next = HEAD_ListAntrean;
    HEAD_ListAntrean = newList;
}

listAntrean *getListAntreanByBuku(Buku *buku) {
    if (HEAD_ListAntrean == NULL) {
        listAntrean *newList = createListAntrean();
        if (!newList) return NULL;
        insertListAntrean(newList);
        return newList;
    }

    for (listAntrean *curr = HEAD_ListAntrean; curr; curr = curr->next) {
        for (Peminjam *p = curr->antrean; p; p = p->nextPeminjam) {
            if (p->nextBuku == buku) {
                return curr;
            }
        }
    }

    listAntrean *newList = createListAntrean();
    if (!newList) return NULL;
    insertListAntrean(newList);
    return newList;
}

listAntrean *getListAntreanByBukuNull(Buku *buku) {
    if (!HEAD_ListAntrean || !buku) return NULL;

    for (listAntrean *curr = HEAD_ListAntrean; curr; curr = curr->next) {
        for (Peminjam *p = curr->antrean; p; p = p->nextPeminjam) {
            if (p->nextBuku == buku) {
                return curr;
            }
        }
    }

    return NULL;
}

void clearListAntrean() {
    listAntrean *curr = HEAD_ListAntrean;
    while (curr) {
        listAntrean *next = curr->next;
        Peminjam *p = curr->antrean;
        while (p) {
            Peminjam *temp = p;
            p = p->nextPeminjam;
            free(temp);
        }
        free(curr);
        curr = next;
    }
    HEAD_ListAntrean = NULL;
}

