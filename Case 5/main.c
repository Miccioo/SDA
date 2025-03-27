#include <stdio.h>
#include <stdlib.h>
#include "case5.h"
#include "string.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int index = 0, opsi = 0;
	char *nama = (char *)malloc(50 * sizeof(char));
	
	for (int i = 0; i < MAX_KOTA; i++) {
		createKota(A, i);
	}
	
	strcpy(A[0].namaKota, "Cimahi");
	strcpy(A[1].namaKota, "Bandung");
	strcpy(A[2].namaKota, "Cianjur");
	strcpy(A[3].namaKota, "Los Angeles");
	strcpy(A[4].namaKota, "Miami");
	
	tambahOrangFirst(A, 0, "Jaki");
	tambahOrangLast(A, 0, "Rahmat");
	tambahOrangFirst(A, 1, "Leni");
	tambahOrangLast(A, 1, "Ningsih");
	tambahOrangFirst(A, 2, "Neneng");
	tambahOrangLast(A, 2, "Mamat");
	tambahOrangFirst(A, 3, "Kevin");
	tambahOrangLast(A, 3, "Olivia");
	tambahOrangFirst(A, 4, "Jakar");
	tambahOrangLast(A, 4, "Manawi");
	
	for(;;) {
		printf("==== SIMULASI WALIKOTA ====\n");
		printKota(A);
		printf("Pilih Kota yang ingin diubah: ");
		scanf("%d", &index);
		tampilMenu();
		printf("\nPilih opsi: ");
		scanf("%d", &opsi);
		switch (opsi) {
			case 1: 
				printf("Masukkan nama orang: ");
				scanf("%49s", nama);
				tambahOrangFirst(A, index, nama);
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			case 2:
				printf("Masukkan nama orang: ");
				scanf("%49s", nama);
				tambahOrangLast(A, index, nama);
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			case 3:
				printf("Masukkan nama orang: ");
				scanf("%49s", nama);
				hapusOrangByNama(A, index, nama);
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			case 4:
				hapusOrangFirst(A, index);
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			case 5:
				hapusOrangLast(A, index);
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			case 6:
				printOrang(A, index);
				getchar();
				getchar();
				continue;
			default:
				printf("Pilihan tidak ada di dalam opsi!");
				continue;
		}
	}
	
	
	return 0;
}
