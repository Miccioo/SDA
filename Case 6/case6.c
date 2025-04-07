#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "case6.h"

/* Check if the list of cities is empty */
boolean ListKotaEmpty(ListKota L) {
    return (First(L) == Nil);
}

/* Create an empty list of cities */
void CreateListKota(ListKota *L) {
    First(*L) = Nil;
}

/* Allocate memory for a new city element */
addressKota AlokasiKota(Kota X) {
    addressKota P = (addressKota) malloc(sizeof(ElmtKota));
    if (P != Nil) {
        P->info = X;
        P->next = Nil;
    }
    return P;
}

/* Deallocate memory for a city element */
void DeAlokasiKota(addressKota P) {
    free(P);
}

/* Search for a city by name in the list */
addressKota SearchKota(ListKota L, char *namaKota) {
    addressKota P = First(L);
    boolean found = false;
    
    while (P != Nil && !found) {
        if (strcmp(P->info.namaKota, namaKota) == 0) {
            found = true;
        } else {
            P = P->next;
        }
    }
    
    return P;
}

/* Insert a new city at the beginning of the list */
void InsertFirstKota(ListKota *L, addressKota P) {
    P->next = First(*L);
    First(*L) = P;
}

/* Insert a new city after a specific city in the list */
void InsertAfterKota(ListKota *L, addressKota P, addressKota Prec) {
    if (Prec != Nil) {
        P->next = Prec->next;
        Prec->next = P;
    }
}

/* Insert a new city at the end of the list */
void InsertLastKota(ListKota *L, addressKota P) {
    if (ListKotaEmpty(*L)) {
        InsertFirstKota(L, P);
    } else {
        addressKota last = First(*L);
        while (last->next != Nil) {
            last = last->next;
        }
        InsertAfterKota(L, P, last);
    }
}

/* Delete the first city from the list */
void DeleteFirstKota(ListKota *L, addressKota *P) {
    if (!ListKotaEmpty(*L)) {
        *P = First(*L);
        First(*L) = (*P)->next;
        (*P)->next = Nil;
    }
}

/* Delete a city after a specific city in the list */
void DeleteAfterKota(ListKota *L, addressKota *Pdel, addressKota Prec) {
    if (Prec != Nil) {
        *Pdel = Prec->next;
        if (*Pdel != Nil) {
            Prec->next = (*Pdel)->next;
            (*Pdel)->next = Nil;
        }
    }
}

/* Delete the last city from the list */
void DeleteLastKota(ListKota *L, addressKota *P) {
    if (!ListKotaEmpty(*L)) {
        if (First(*L)->next == Nil) {
            DeleteFirstKota(L, P);
        } else {
            addressKota last = First(*L);
            addressKota precLast = Nil;
            
            while (last->next != Nil) {
                precLast = last;
                last = last->next;
            }
            
            *P = last;
            DeleteAfterKota(L, P, precLast);
        }
    }
}

/* Delete a city by name from the list */
void DeleteKotaByName(ListKota *L, char *namaKota) {
    if (!ListKotaEmpty(*L)) {
        addressKota P = First(*L);
        addressKota Prec = Nil;
        boolean found = false;
        
        while (P != Nil && !found) {
            if (strcmp(P->info.namaKota, namaKota) == 0) {
                found = true;
            } else {
                Prec = P;
                P = P->next;
            }
        }
        
        if (found) {
            if (Prec == Nil) {
                DeleteFirstKota(L, &P);
            } else {
                DeleteAfterKota(L, &P, Prec);
            }
            DeAlokasiKota(P);
        }
    }
}

/* Add a new city to the list */
void AddKota(ListKota *L, char *namaKota) {
    // Check if city already exists
    addressKota P = SearchKota(*L, namaKota);
    
    if (P == Nil) {
        // Create a new city
        Kota newKota;
        strcpy(newKota.namaKota, namaKota);
        CreateList(&(newKota.daftarOrang));
        
        // Allocate memory and add to list
        P = AlokasiKota(newKota);
        if (P != Nil) {
            InsertLastKota(L, P);
            printf("Kota %s berhasil ditambahkan.\n", namaKota);
        } else {
            printf("Gagal menambahkan kota (alokasi memori gagal).\n");
        }
    } else {
        printf("Kota %s sudah ada dalam daftar.\n", namaKota);
    }
}

/* Add a person to a specific city */
void AddOrangToKota(ListKota *L, char *namaKota, char *namaOrang) {
    addressKota P = SearchKota(*L, namaKota);
    
    if (P != Nil) {
        InsVLast(&(P->info.daftarOrang), namaOrang);
        printf("%s berhasil ditambahkan ke kota %s.\n", namaOrang, namaKota);
    } else {
        printf("Kota %s tidak ditemukan.\n", namaKota);
    }
}

/* Remove a person from a specific city */
void RemoveOrangFromKota(ListKota *L, char *namaKota, char *namaOrang) {
    addressKota P = SearchKota(*L, namaKota);
    
    if (P != Nil) {
        address Q = Search(P->info.daftarOrang, namaOrang);
        if (Q != Nil) {
            DelP(&(P->info.daftarOrang), namaOrang);
            printf("%s berhasil dihapus dari kota %s.\n", namaOrang, namaKota);
        } else {
            printf("%s tidak ditemukan di kota %s.\n", namaOrang, namaKota);
        }
    } else {
        printf("Kota %s tidak ditemukan.\n", namaKota);
    }
}

/* Print all cities and people in them */
void PrintAllCitiesAndPeople(ListKota L) {
    addressKota P = First(L);
    int count = 1;
    
    if (ListKotaEmpty(L)) {
        printf("Tidak ada kota yang terdaftar.\n");
        return;
    }
    
    printf("===== DAFTAR KOTA DAN PENDUDUK =====\n");
    while (P != Nil) {
        printf("%d. Kota: %s\n", count, P->info.namaKota);
        printf("   Penduduk:\n");
        
        if (ListEmpty(P->info.daftarOrang)) {
            printf("   - Tidak ada penduduk terdaftar\n");
        } else {
            address Q = First(P->info.daftarOrang);
            int personCount = 1;
            
            while (Q != Nil) {
                printf("   %d. %s\n", personCount, Info(Q));
                Q = Next(Q);
                personCount++;
            }
        }
        
        P = P->next;
        count++;
        printf("\n");
    }
}

/* Print people in a specific city */
void PrintPeopleInCity(ListKota L, char *namaKota) {
    addressKota P = SearchKota(L, namaKota);
    
    if (P != Nil) {
        printf("Penduduk di Kota %s:\n", namaKota);
        
        if (ListEmpty(P->info.daftarOrang)) {
            printf("- Tidak ada penduduk terdaftar\n");
        } else {
            // Custom implementation for printing people
            address Q = First(P->info.daftarOrang);
            int i = 1;
            
            while (Q != Nil) {
                printf("%d. %s\n", i, Info(Q));
                Q = Next(Q);
                i++;
            }
        }
    } else {
        printf("Kota %s tidak ditemukan.\n", namaKota);
    }
}

/* Display interface menu for city and people management */
void displayMenu() {
    printf("\n===== MANAJEMEN KOTA DAN PENDUDUK =====\n");
    printf("1. Tambah Kota Baru\n");
    printf("2. Hapus Kota\n");
    printf("3. Tambah Penduduk ke Kota\n");
    printf("4. Hapus Penduduk dari Kota\n");
    printf("5. Tampilkan Semua Kota dan Penduduk\n");
    printf("6. Tampilkan Penduduk di Kota Tertentu\n");
    printf("0. Keluar\n");
    printf("Pilihan: ");
}
