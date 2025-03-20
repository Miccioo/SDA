#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	// Kamus Data
	infotype angka;
	Stack A;
	
	// Membuat Stack A
	createStack(&A);
	
	printf("Masukkan angka decimal untuk di convert menjadi binary : ");
	scanf("%d", &angka);
	Binary(&A, angka); // Mengonversi dari angka decimal ke binary
	
	printf("Binary: ");
	display(A);
	
	return 0;
}
