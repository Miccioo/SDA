#include "buku.h"

Buku *HEAD_Buku = NULL;

void initList() {
    HEAD_Buku = NULL;
}

int isListBukuEmpty() {
    return HEAD_Buku == NULL;
}

int isBukuExist(char judul[]) {
    Buku *curr = HEAD_Buku;
    while (curr) {
        if (strcmp(curr->judul, judul) == 0) return 1;
        curr = curr->next;
    }
    return 0;
}

Buku *createBuku(char judul[], int stock) {
    Buku *b = malloc(sizeof(Buku));
    if (!b) return NULL;
    strcpy(b->judul, judul);
    b->stock = stock;
    b->next = NULL;
    return b;
}

void insertBuku(char judul[], int stock) {
    if (isBukuExist(judul)) return;
    Buku *b = createBuku(judul, stock);
    if (!b) return;
    b->next = HEAD_Buku;
    HEAD_Buku = b;
}

void deleteBuku(char judul[]) {
    if (isListBukuEmpty()) return;
    Buku *curr = HEAD_Buku, *prev = NULL;
    while (curr && strcmp(curr->judul, judul) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;
    if (!prev) HEAD_Buku = curr->next;
    else prev->next = curr->next;
    free(curr);
}

Buku *findBuku(char judul[]) {
    Buku *curr = HEAD_Buku;
    while (curr) {
        if (strcmp(curr->judul, judul) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

void clearListBuku() {
    while (!isListBukuEmpty()) {
        deleteBuku(HEAD_Buku->judul);
    }
}

