#include "case5.h"
#include "linked.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

Kota A[MAX_KOTA];

boolean kotaEmpty(Kota L) {
/* Mengirim true jika Kota Kosong */
    return (L.daftarOrang.First == Nil);
}

void createKota(Kota *L, int index) {
	L[index].namaKota[0] = "\0"; 		// Membuat string kosong
	CreateList(&(L[index].daftarOrang));
}

void deleteKota(Kota *L, int index) {
	if (index < 0 || index >= MAX_KOTA) return;
	
	address current = First(L[index].daftarOrang);
	while (current != Nil) {
		address temp = current;
		current = Next(current);
		free(Info(temp));
		DeAlokasi(temp);
	}

	L[index].namaKota[0] = '\0';
}

void tambahOrangFirst(Kota *L, int index, char *nama) {
	
	char *namaCopy = strdup(nama);
	
	address newNode = Alokasi(namaCopy);
	InsertFirst(&L[index].daftarOrang, newNode);
}

void tambahOrangLast(Kota *L, int index, char *nama) {
	
	char *namaCopy = strdup(nama);

	address newNode = Alokasi(namaCopy);
	InsertLast(&L[index].daftarOrang, newNode);
}

void hapusOrangByNama (Kota *L, int index, char *nama) {
	
	char *namaCopy = strdup(nama);
	
//	address current  = Search(L[index].daftarOrang, namaCopy);
	DelP(&L[index].daftarOrang, namaCopy);
}

void hapusOrangFirst (Kota *L, int index) {
	
	address current = First(L[index].daftarOrang);
	DelFirst(&L[index].daftarOrang, &current);

}

void hapusOrangLast (Kota *L, int index) {
	
	address current = First(L[index].daftarOrang);
	DelLast(&L[index].daftarOrang, &current);
}

void printKota(Kota *L) {
	
	printf("Kota yang ada saat ini: \n");
    for(int i = 0; i < MAX_KOTA; i++) {
        // Cek apakah kota terisi
        if(strlen(A[i].namaKota) > 1) { 
            printf("%d. %s\n", i+1, A[i].namaKota);
        }
    }
}

void printOrang(Kota *L, int index) {
    // Validasi index
    if (index < 0 || index >= MAX_KOTA) {
        printf("Error: Index kota tidak valid!\n");
        return;
    }

    // Cek apakah kota ada
    if (strlen(L[index].namaKota) == 0) {
        printf("Error: Kota pada index %d tidak terdaftar!\n", index);
        return;
    }

    address current = First(L[index].daftarOrang);
    
    // Cek apakah ada penduduk
    if (current == Nil) {
        printf("Kota %s belum memiliki penduduk.\n", L[index].namaKota);
        return;
    }

    printf("\nPenduduk di Kota %s:\n", L[index].namaKota);
    
    int counter = 1;
    while (current != Nil) {
        printf("%d. %s\n", counter, (char*)Info(current)); // Cast ke char* jika infotype adalah void*
        current = Next(current);
        counter++;
    }
}

void tampilMenu() {
	printf("1. Tambah orang pertama\n");
	printf("2. Tambah orang terakhir\n");
	printf("3. Hilangkan orang dari nama\n");
	printf("4. Hilangkan orang pertama\n");
	printf("5. Hilangkan orang terakhir\n");
	printf("6. Tampilkan penduduk dari kota");
}
