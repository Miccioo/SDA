#include "src.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createList(List *list){
    list->First = Nil;
    list->Last = Nil;
}

address createNode(char nama[], infotype nilaiUTS){
    address newNode = (address)malloc(sizeof(ElmtList));
    if (newNode == Nil){
        printf("Error: Gagal mengalokasi malloc di createNode\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nama(newNode), nama);
    nilai(newNode) = nilaiUTS;
    next(newNode) = Nil;
    return newNode;
}

void deleteList(List *L) {
    address cur = L->First;
    while (cur != Nil) {
        address temp = cur;
        cur = cur->next;
        free(temp);
    }
    L->First = Nil;
    L->Last = Nil;
}

int isEmpty(address list) {
    return list == Nil;
}

char* getNama(address node) {
    if (node != Nil) {
        return node->info.nama;
    } else {
        return "Node tidak valid!";
    }
}

infotype getNilaiUTS(address node) {
    if (node != Nil) {
        return node->info.nilai;
    } else {
        return -1; // Nilai default jika node tidak valid
    }
}

void setMahasiswa(address list, char nama[], infotype nilaiUTS){
    if (!isEmpty(list)) {
        strcpy(nama(list), nama);
        nilai(list) = nilaiUTS;
    } else {
        printf("List tidak ada!. Gagal memperbarui data!");
    }
}

void printObject(address list) {
    while (list != Nil) {
        printf("Nama: %s, Nilai UTS: %d\n", nama(list), nilai(list));
        list = next(list);
    }
}

void DescendingByNilai(address list) {
    if (list == Nil) {
        printf("List kosong!\n");
        return;
    }

    // Hitung jumlah elemen
    int count = 0;
    address cur = list;
    while (cur != Nil) {
        count++;
        cur = cur->next;
    }

    // Buat array untuk menyimpan nilai dan nama
    int nilaiArray[count];
    char namaArray[count][MAXCHAR];
    cur = list;
    for (int i = 0; i < count; i++) {
        nilaiArray[i] = getNilaiUTS(cur);
        strcpy(namaArray[i], getNama(cur));
        cur = cur->next;
    }

    // Urutkan array secara descending berdasarkan nilai
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (nilaiArray[i] < nilaiArray[j]) {
                // Tukar nilai
                int tempNilai = nilaiArray[i];
                nilaiArray[i] = nilaiArray[j];
                nilaiArray[j] = tempNilai;

                // Tukar nama
                char tempNama[MAXCHAR];
                strcpy(tempNama, namaArray[i]);
                strcpy(namaArray[i], namaArray[j]);
                strcpy(namaArray[j], tempNama);
            }
        }
    }

    // Tampilkan hasil pengurutan
    for (int i = 0; i < count; i++) {
        printf("Nama: %s, Nilai UTS: %d\n", namaArray[i], nilaiArray[i]);
    }
}

address insertSort(address *list, char nama[], infotype nilaiUTS) {
    address newNode = createNode(nama, nilaiUTS); // Buat node baru
    if (newNode == Nil) {
        return *list; // Gagal membuat node baru
    }

    // Jika list kosong atau node baru harus menjadi head
    if (*list == Nil || strcmp(nama(*list), nama) >= 0) {
        next(newNode) = *list;
        *list = newNode;
        return *list;
    }

    // Cari posisi yang tepat untuk menyisipkan node baru
    address cur = *list;
    while (next(cur) != Nil && strcmp(nama(next(cur)), nama) < 0) {
        cur = next(cur);
    }

    // Sisipkan node baru
    next(newNode) = next(cur);
    next(cur) = newNode;

    return *list; // Kembalikan head yang baru
}

int countElements(List L) {
    int count = 0;
    address cur = L.First;
    while (cur != Nil) {
        count++;
        cur = next(cur);
    }
    return count;
}

void removeDuplicates(List *L) {
    if (L->First == Nil) {
        return; // List kosong, tidak ada yang dihapus
    }

    address cur = L->First;
    while (cur != Nil && cur->next != Nil) {
        address temp = cur;
        while (temp->next != Nil) {
            if (strcmp(getNama(cur), getNama(temp->next)) == 0) {
                // Hapus node duplikat
                address duplicate = temp->next;
                temp->next = temp->next->next;
                free(duplicate);
            } else {
                temp = temp->next;
            }
        }
        cur = cur->next;
    }
}

address insertLast(address *list, char nama[], infotype nilaiUTS) {
    address newNode = createNode(nama, nilaiUTS); // Buat node baru
    if (newNode == Nil) {
        return *list; // Gagal membuat node baru
    }

    // Jika list kosong, node baru menjadi head
    if (*list == Nil) {
        *list = newNode;
        return *list;
    }

    // Iterasi sampai node terakhir
    address cur = *list;
    while (next(cur) != Nil) {
        cur = next(cur);
    }

    // Sisipkan node baru di akhir
    next(cur) = newNode;
    return *list; // Kembalikan head yang baru
}
