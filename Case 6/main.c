#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "case5.h"
#include "case6.h"

// Initialize the array of cities for case5
Kota A[MAX_KOTA];

// Function prototypes for menu handling
void menuCase5();
void menuCase6();

int main() {
    ListKota listKota;
    CreateListKota(&listKota);

    char namaKota[20], namaOrang[50];
    int choice;
    
    for (int i = 0; i < MAX_KOTA; i++) {
        createKota(A, i);
        A[i].namaKota[0] = '\0';
    }
    
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Masukkan nama kota baru: ");
                scanf("%s", namaKota);
                AddKota(&listKota, namaKota);
                break;
                
            case 2:
                printf("Masukkan nama kota yang akan dihapus: ");
                scanf("%s", namaKota);
                
                addressKota cityToDelete = SearchKota(listKota, namaKota);
                if (cityToDelete != NULL) {
                    DeleteKotaByName(&listKota, namaKota);
                    printf("Kota %s berhasil dihapus.\n", namaKota);
                } else {
                    printf("Kota %s tidak ditemukan.\n", namaKota);
                }
                break;
                
            case 3:
                printf("Masukkan nama kota: ");
                scanf("%s", namaKota);
                
                addressKota cityToAddPerson = SearchKota(listKota, namaKota);
                if (cityToAddPerson != NULL) {
                    printf("Masukkan nama orang: ");
                    scanf("%s", namaOrang);
                    AddOrangToKota(&listKota, namaKota, strdup(namaOrang));
                } else {
                    printf("Kota %s tidak ditemukan.\n", namaKota);
                }
                break;
                
            case 4:
                printf("Masukkan nama kota: ");
                scanf("%s", namaKota);
                
                addressKota cityToRemovePerson = SearchKota(listKota, namaKota);
                if (cityToRemovePerson != NULL) {
                    printf("Masukkan nama orang yang akan dihapus: ");
                    scanf("%s", namaOrang);
                    RemoveOrangFromKota(&listKota, namaKota, namaOrang);
                } else {
                    printf("Kota %s tidak ditemukan.\n", namaKota);
                }
                break;
                
            case 5:
                PrintAllCitiesAndPeople(listKota);
                break;
                
            case 6: 
                printf("Masukkan nama kota: ");
                scanf("%s", namaKota);
                PrintPeopleInCity(listKota, namaKota);
                break;
                
            case 0: // Exit
                printf("Kembali ke menu utama...\n");
                break;
                
            default:
                printf("Pilihan tidak valid!\n");
        }
        
    } while (choice != 0);
    
    addressKota P, temp;
    P = First(listKota);
    while (P != NULL) {
        temp = P;
        P = P->next;

        address Q, tempQ;
        Q = First(temp->info.daftarOrang);
        while (Q != NULL) {
            tempQ = Q;
            Q = Next(Q);
            DeAlokasi(tempQ);
        }
        
        DeAlokasiKota(temp);
    }
}
