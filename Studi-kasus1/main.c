#include <stdio.h>
#include <stdlib.h>
#include "src.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	// 2. Membuat L1 dan L2 yang menampung data mahasiswa
	List L1, L2;
    createList(&L1);
    createList(&L2);

    // 3. Menambahkan data mahasiswa ke L1 secara ascending berdasarkan nama
    L1.First = insertSort(&L1.First, "Zahran Ramadhan", 50);
    L1.First = insertSort(&L1.First, "Dimas Maulana", 60);
    L1.First = insertSort(&L1.First, "Dimas Maulana", 60);
    L1.First = insertSort(&L1.First, "Mahardika", 75);
    L1.First = insertSort(&L1.First, "Mahardika", 75);
	L1.First = insertSort(&L1.First, "Rayhan", 85);
    L1.First = insertSort(&L1.First, "Ahmad Khairul", 85);
    L1.First = insertSort(&L1.First, "Andika Dimas", 90);
    L1.First = insertSort(&L1.First, "Nabil Akhmad", 80);
    L1.First = insertSort(&L1.First, "Ahmad Khairul", 75); // Data duplikat untuk testing

    // 4. Tampilkan isi List L1 (Nama, Nilai UTS) terurut ascending berdasarkan nama
    printf("Isi List L1 (ascending berdasarkan nama):\n");
    printObject(L1.First);

    // 5. Tampilkan isi List L1 (Nama, Nilai UTS) terurut descending berdasarkan nilai
    printf("\nIsi List L1 (descending berdasarkan nilai):\n");
    DescendingByNilai(L1.First);
    
    // 6. Hitung jumlah elemen (jumlah mahasiswa pada list), kemudian tampilkan
    int jumlahElemen = countElements(L1);
    printf("\nJumlah mahasiswa pada List L1: %d\n", jumlahElemen);

    // 7. Copy seluruh elemen pada List L1 yang Nilainya > 70 ke List L2
    address cur = L1.First;
    while (cur != Nil) {
        if (getNilaiUTS(cur) > 70) {
            L2.First = insertLast(&L2.First, getNama(cur), getNilaiUTS(cur));
        }
        cur = next(cur);
    }

    // 8. Tampilkan isi elemen List L2
    printf("\nIsi List L2 (nilai > 70):\n");
    printObject(L2.First);

    // 9. Jika pada L2 ada yang namanya sama, hapus data duplikat (bukan yang pertama)
    removeDuplicates(&L2);

    // 10. Tampilkan elemen List L2 yang baru (setelah menghapus duplikat)
    printf("\nIsi List L2 setelah menghapus duplikat:\n");
    printObject(L2.First);

    // 11. Hapus List L1 dan List L2
    deleteList(&L1);
    deleteList(&L2);

    // Memeriksa apakah list kosong setelah dihapus
    if (isEmpty(L1.First) && isEmpty(L2.First)) {
        printf("\nList L1 dan L2 telah dihapus dan kosong.\n");
    }

    return 0;
}
